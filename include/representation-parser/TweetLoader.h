/*
 * Created by rdelfin on 11/29/15.
 */

#ifndef TWITTER_DATA_TOOLS_TWEETLOADER_H
#define TWITTER_DATA_TOOLS_TWEETLOADER_H

#include <string>
#include <fstream>
#include <thread>
#include <mutex>
#include <exception>

#include "tools-lib/csv.h"

#define NUM_TWEET_LOADER_THREADS 20
#define TASK_SIZE 500

class Dictionary;
class Tweet;

class tasks_running_exception: public std::exception
{
    virtual const char* what() const throw()
    {
        return "A task is still running in the TweetLoader. Please wait for it to finish.";
    }
};


typedef struct pair_struct {
    size_t min;
    size_t max;

    bool operator==(const pair_struct& rhs) {
        return min == rhs.min && max == rhs.max;
    }
} Pair;

typedef struct {
    Pair pair;
    std::thread thread;
} ThreadTask;

class TweetLoader {
public:
    TweetLoader();
    TweetLoader(std::string data_file, Dictionary *dictionary);

    void load();

    std::vector<Tweet> parse();

    ~TweetLoader();
private:
    std::vector<Pair> tasks;
    std::vector<ThreadTask*> threadList;

    void threadScheduler();
    void parseRange(size_t min, size_t max);

    std::vector<std::string> tweetStrings;
    io::CSVReader<6, io::trim_chars<' ', '\t'>, io::double_quote_escape<',', '"'>>* reader;
    Dictionary* dictionary;
    std::vector<Tweet> tweetList;

    static const std::string SCRIPT_PATH;

    std::string cwd;

    std::mutex tweetMutex;

    std::mutex threadListMutex;
    std::condition_variable threadListCV;
    unsigned startedThreadCount, completedThreadCount;
};



#endif //TWITTER_DATA_TOOLS_TWEETLOADER_H
