//
// Created by rdelfin on 11/29/15.
//

#include <tools-lib/StringUtils.h>
#include <sstream>
#include <iostream>
#include <unistd.h>
#include "representation-parser/TweetLoader.h"
#include "representation-parser/Dictionary.h"
#include "representation-parser/Tweet.h"

const std::string TweetLoader::SCRIPT_PATH = "/config/ark-tweet-nlp-0.3.2/twokenize.sh";

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
        tweets.push_back(tl::StringUtils::trim(tweet));
    }
}

std::vector<Tweet> TweetLoader::parse() {
    
}

TweetLoader::TweetLoader() {

}
