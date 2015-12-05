//
// Created by rdelfin on 11/29/15.
//

#include <tools-lib/StringUtils.h>
#include <sstream>
#include <iostream>
#include <unistd.h>
#include <algorithm>
#include <tools-lib/Process.h>
#include <representation-parser/TweetLoader.h>
#include <representation-parser/Configuration.h>
#include "representation-parser/Dictionary.h"
#include "representation-parser/Tweet.h"


TweetLoader::~TweetLoader() {

}

TweetLoader::TweetLoader(std::string data_file, Dictionary* dictionary)
    : dictionary(dictionary)
{
    char cwd_buffer[512];
    getcwd(cwd_buffer, sizeof(cwd_buffer));
    cwd = std::string(cwd_buffer);

    reader = new io::CSVReader<6, io::trim_chars<' ', '\t'>, io::double_quote_escape<',', '"'>>((cwd + data_file).c_str());
}

void TweetLoader::load() {
    reader->read_header(io::ignore_extra_column, "sentiment", "index", "date", "query", "topic", "tweet");
    std::string sentiment, index, date, query, topic, tweet;
    while(reader->read_row(sentiment, index, date, query, topic, tweet)) {
        tweetStrings.push_back(tl::StringUtils::trim(tweet));
    }
}

std::vector<Tweet> TweetLoader::parse() {
    if(threadList.size() != 0) {
        std::cerr << "Error: Thread list is not empty. Wait for the computation to finish." << std::endl;
        throw tasks_running_exception();
    }

    if(tasks.size() != 0) {
        std::cerr << "Error: Task list is not empty. Wait for the computation to finish." << std::endl;
        throw tasks_running_exception();
    }

    startedThreadCount = completedThreadCount = 0;

    for(size_t i = 0; i < tweetStrings.size(); i += TASK_SIZE) {
        Pair task;
        task.min = i;
        task.max = i + TASK_SIZE - 1;
        tasks.push_back(task);
        std::cerr << "TASK: [" << task.min << ", " << task.max << "]" << std::endl;
    }

    std::cerr << "CREATED A TOTAL OF " << tasks.size() << " TASKS" << std::endl << std::endl;

    threadScheduler();

    return tweetList;
}

void TweetLoader::threadScheduler() {
    std::unique_lock<std::mutex> threadListLock(threadListMutex);

    while(tasks.size() != 0) {

        while (threadList.size() >= NUM_TWEET_LOADER_THREADS) {
            threadListCV.wait(threadListLock);
        }

        while (threadList.size() < NUM_TWEET_LOADER_THREADS) {
            Pair lastTask = tasks[tasks.size() - 1];
            tasks.pop_back();
            ThreadTask *newTask = new ThreadTask;
            newTask->pair = lastTask;
            newTask->thread = std::thread(&TweetLoader::parseRange, this, lastTask.min, lastTask.max);
            threadList.push_back(newTask);
            threadList[threadList.size() - 1]->thread.detach();
        }

    }

    while (threadList.size() != 0)
        threadListCV.wait(threadListLock);

    threadListLock.unlock();
}


void TweetLoader::parseRange(size_t min, size_t max)
{
    startedThreadCount++;
    std::cerr << "Parsing tweet range: [" << min << ", " << max << "]. Task #" << startedThreadCount << std::endl;

    tl::Process p("/bin/sh", {Configuration::instance()->tokenizer()});

    std::stringstream& in = p.stdin();

    for(size_t i = min; i <= std::min(max, tweetStrings.size() - 1); i++) {
        in << tweetStrings[i] << std::endl;
    }

    // Start the program and wait (no input).
    p.start();
    p.wait();

    // Get the output and parse data
    std::stringstream& out = p.stdout();


    std::cerr << "Adding tweets" << std::endl;

    std::unique_lock<std::mutex> tweetLock(tweetMutex);

    std::string line;
    size_t tweetidx = 0;
    while(std::getline(out, line)) {
        std::vector<std::string> tweet = tl::StringUtils::split(line, '\t');
        tweetList.push_back(Tweet(tweet[0], dictionary));
    }

    tweetLock.unlock();

    std::unique_lock<std::mutex> threadListLock(threadListMutex);

    Pair task;
    task.min = min;
    task.max = max;
    for(unsigned i = 0; i < threadList.size(); i++) {
        if (task == threadList[i]->pair) {
            delete threadList[i];
            threadList[i] = threadList[threadList.size() - 1];
            threadList.pop_back();
            break;
        }
    }

    threadListCV.notify_one();

    completedThreadCount++;
    std::cerr << "Completed thread with tweet range: [" << min << ", " << max << "]. Threads completed: " << completedThreadCount << std::endl;
}


TweetLoader::TweetLoader() {

}
