//
// Created by rdelfin on 12/5/15.
//

#ifndef TWITTER_DATA_TOOLS_OUTPUTGENERATOR_H
#define TWITTER_DATA_TOOLS_OUTPUTGENERATOR_H

#include <vector>
#include <fstream>

class Dictionary;
class Tweet;

class OutputGenerator {
public:
    OutputGenerator(std::vector<Tweet>& tweets, Dictionary* dictionary);

    ~OutputGenerator();

    void open();

    void writeOut();


private:
    Dictionary* dictionary;
    std::vector<Tweet>& tweets;

    std::ofstream dictionaryFile, tweetsFile;

    void writeDictionary();
    void writeTweets();
};


#endif //TWITTER_DATA_TOOLS_OUTPUTGENERATOR_H
