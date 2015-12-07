//
// Created by rdelfin on 12/5/15.
//

#include "representation-parser/OutputGenerator.h"

#include <representation-parser/Dictionary.h>
#include <representation-parser/DictionaryEntry.h>
#include <representation-parser/Tweet.h>
#include <representation-parser/Configuration.h>

#include <sys/stat.h>
#include <tools-lib/csv.h>

OutputGenerator::OutputGenerator(std::vector<Tweet> &tweets, Dictionary *dictionary) :
    tweets(tweets), dictionary(dictionary) {
    open();
}

void OutputGenerator::open() {
    std::string outputDir = Configuration::instance()->output();

    mkdir (outputDir.c_str(), 0777);

    remove((outputDir + "/dictionary.txt").c_str());
    remove((outputDir + "/tweets.txt").c_str());

    dictionaryFile.open(outputDir + "/dictionary.txt", std::ifstream::out | std::ifstream::trunc);
    tweetsFile.open(outputDir + "/tweets.txt", std::ifstream::out | std::ifstream::trunc);
}

OutputGenerator::~OutputGenerator() {
    dictionaryFile.close();
    tweetsFile.close();
}

void OutputGenerator::writeOut() {
    std::thread dictionaryThread(&OutputGenerator::writeDictionary, this);
    std::thread tweetsThread(&OutputGenerator::writeTweets, this);

    dictionaryThread.join();
    tweetsThread.join();
}

void OutputGenerator::writeDictionary() {
    for(size_t i = 0; i < dictionary->dictionarySize(); i++) {
        dictionaryFile << dictionary->entryAt(i)->getName() << std::endl;
    }
}

void OutputGenerator::writeTweets() {
    for (size_t i = 0; i < tweets.size(); i++) {
        for(size_t j = 0; j < tweets[i].size(); j++) {
            tweetsFile << tweets[i][j]->getIdx();
            if(j < tweets[i].size() - 1) {
                tweetsFile << ",";
            }
        }
        tweetsFile << std::endl;
    }
}
