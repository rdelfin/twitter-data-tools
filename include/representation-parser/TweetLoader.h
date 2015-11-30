/*
 * Created by rdelfin on 11/29/15.
 */

#ifndef TWITTER_DATA_TOOLS_TWEETLOADER_H
#define TWITTER_DATA_TOOLS_TWEETLOADER_H

#include <string>
#include <fstream>

#include "tools-lib/csv.h"

class Dictionary;
class Tweet;

class TweetLoader {
public:
    TweetLoader();
    TweetLoader(std::string data_file, Dictionary *dictionary);

    void load();

    std::vector<Tweet> parse();

    ~TweetLoader();
private:
    std::vector<std::string> tweets;
    io::CSVReader<6, io::trim_chars<' ', '\t'>, io::double_quote_escape<',', '"'>>* reader;
    Dictionary* dictionary;

    static const std::string SCRIPT_PATH;

    std::string cwd;
};


#endif //TWITTER_DATA_TOOLS_TWEETLOADER_H
