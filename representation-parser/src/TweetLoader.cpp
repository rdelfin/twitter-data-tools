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
#include <sys/stat.h>
#include "representation-parser/Dictionary.h"
#include "representation-parser/Tweet.h"


TweetLoader::~TweetLoader() {

}

TweetLoader::TweetLoader(std::string data_file, Dictionary* dictionary)
    : dictionary(dictionary)
{
    reader = new io::CSVReader<6, io::trim_chars<' ', '\t'>, io::double_quote_escape<',', '"'>>(data_file.c_str());
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
        printlnAtomic("Error: Thread list is not empty. Wait for the computation to finish.");
        throw tasks_running_exception();
    }

    if(tasks.size() != 0) {
        printlnAtomic("Error: Task list is not empty. Wait for the computation to finish.");
        throw tasks_running_exception();
    }

    startedThreadCount = completedThreadCount = 0;

    size_t taskSize = Configuration::instance()->taskSize();

    for(size_t i = 0; i < tweetStrings.size(); i += taskSize) {
        Pair task;
        task.min = i;
        task.max = i + taskSize - 1;
        tasks.push_back(task);

        std::stringstream stream;
        stream << "TASK: [" << task.min << ", " << task.max << "]";
        printlnAtomic(stream.str());
    }

    totalTasks = tasks.size();


    std::stringstream stream;
    stream << "CREATED A TOTAL OF " << tasks.size() << " TASKS" << std::endl;
    printlnAtomic(stream.str());

    threadScheduler();

    return tweetList;
}

void TweetLoader::threadScheduler() {
    /* Directory used by tasks to store twitter data */
    mkdir("temp", 0777);

    std::unique_lock<std::mutex> threadListLock(threadListMutex);

    size_t threadMax = Configuration::instance()->threads();

    while(tasks.size() > 0) {

        while (threadList.size() >= threadMax) {
            threadListCV.wait(threadListLock);
        }

        while (threadList.size() < threadMax && tasks.size() > 0) {
            Pair lastTask = tasks[tasks.size() - 1];
            tasks.pop_back();
            ThreadTask *newTask = new ThreadTask;
            newTask->pair = lastTask;

            std::stringstream stream;
            stream << "Scheduling task [" << lastTask.min << ", " << lastTask.max << "]. Tasks left: " << tasks.size();
            printlnAtomic(stream.str());
            newTask->thread = std::thread(&TweetLoader::parseRange, this, lastTask.min, lastTask.max);
            threadList.push_back(newTask);
            threadList[threadList.size() - 1]->thread.detach();
        }

    }

    while (threadList.size() != 0)
        threadListCV.wait(threadListLock);

    rmdir("temp");

    threadListLock.unlock();
}


void TweetLoader::parseRange(size_t min, size_t max)
{
    startedThreadCount++;

    std::stringstream data;

    for(size_t i = min; i <= std::min(max, tweetStrings.size() - 1); i++) {
        data << tweetStrings[i] << std::endl;
    }

    std::stringstream fname;
    fname << "temp/" << min << "_" << max << ".txt";
    std::ofstream tempData(fname.str(), std::ofstream::out | std::ofstream::trunc);

    tempData << data.str();
    tempData.close();

    tl::Process p("/bin/sh", {Configuration::instance()->tokenizer(), fname.str()});

    // Start the program and wait (no input).
    p.start();
    p.wait();

    unlink(fname.str().c_str());

    // Get the output and parse data
    std::stringstream& out = p.stdout();

    std::unique_lock<std::mutex> tweetLock(tweetMutex);

    std::stringstream addTweetsStream;
    addTweetsStream << "Adding tweets with tweet range: [" << min << ", " << max << "]";
    printlnAtomic(addTweetsStream.str());

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

    std::stringstream stream2;
    stream2 << "Completed thread with tweet range: [" << min << ", " << max << "]. Threads completed: "
            << completedThreadCount << "/" << totalTasks;
    printlnAtomic(stream2.str());

    threadListLock.unlock();
}

void TweetLoader::printlnAtomic(std::string str)
{
    std::unique_lock<std::mutex> printLock(printMutex);
    std::cerr << str << std::endl;
    printLock.unlock();
}

TweetLoader::TweetLoader() {

}
