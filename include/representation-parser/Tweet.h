//
// Created by rdelfin on 11/28/15.
//

#ifndef TWITTER_DATA_TOOLS_TWEET_H
#define TWITTER_DATA_TOOLS_TWEET_H

#include <vector>
#include <string>

class DictionaryEntry;
class Dictionary;

class Tweet {
public:
    Tweet();
    Tweet(std::string tokenizedTweet, Dictionary*);

    size_t size();
    DictionaryEntry* operator[](size_t idx);

    ~Tweet();
private:
    std::vector<DictionaryEntry *> tokens;
    Dictionary* dict;
};


#endif //TWITTER_DATA_TOOLS_TWEET_H
