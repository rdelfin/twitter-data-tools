/*
 * Created by Ricardo Delfin Garcia on 11/24/15.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <representation-parser/Dictionary.h>
#include <representation-parser/DictionaryEntry.h>
#include <tools-lib/StringUtils.h>
#include <representation-parser/Tweet.h>
#include <representation-parser/TweetLoader.h>

#include "tools-lib/Process.h"

inline unsigned num_len(unsigned n);
inline void remove_from_stdout(unsigned chars);

int main(int argc, char* argv[]) {

    /* Get the current working directory, where the config directory should be located */

    // TODO: Move these declarations into a json config file... Or something.
    /* Define paths for the tokenize script as well as the data. These are at constant locations */
    std::string dataPath = "/config/twitter-data/training.1600000.processed.noemoticon.csv";

    std::cout << "Starting..." << std::endl;

    Dictionary dict;

    TweetLoader tl(dataPath, &dict);
    tl.load();

    std::cout << "Done!" << std::endl;

    // Runs the twokenize script with the default shell.
    /*tl::Process p("/bin/sh", {scriptPath, dataPath});

    // Start the program and wait (no input).
    p.start();
    p.wait();

    // Get the output and parse data
    std::stringstream& ss = p.stdout();

    Dictionary dictionary;

    // Regex for handles
    dictionary.insertRegex("^@[\\w]+$", "TWITTER_HANDLE_TOK");
    // Regex for... url's?
    dictionary.insertRegex("^((http|https):\\/\\/)?(www.)?[\\w-_]+(\\.[\\w-_]+){1,3}((\\/)|(\\/[\\w-_]+\\/?)+|((\\/[\\w-_]+)*\\/[\\w-_]+\\.[\\w-_]+))?$", "URL_TOK");
    // Regex for hashtags (probably should not be here)
    //dictionary.insertRegex("^#\\w+$", "HASHTAG_TOK");



    std::vector<Tweet> tweets;

    std::cout << "Added tweet #0";

    std::string line;
    size_t tweetidx = 0;
    while(std::getline(ss, line)) {
        std::vector<std::string> tweet = tl::StringUtils::split(line, '\t');
        tweets.push_back(Tweet(tweet[0], &dictionary));

        remove_from_stdout(num_len(tweetidx));

        std::cout << ++tweetidx;
        fflush(stdout);
    }

    std::cout << "Unique terms:" << std::endl << std::endl;

    for(size_t i = 0; i < dictionary.dictionarySize(); i++) {
        std::cout << dictionary.entryAt(i)->getName() << std::endl;
    }

    std::cout << "----------------------------" << std::endl;
    std::cout << "Number of unique terms in dictionary: " << dictionary.dictionarySize() << std::endl;*/
}

inline unsigned num_len(unsigned n)
{
    if(n == 0)
        return 1;

    unsigned result = 0;
    while(n != 0) {
        n /= 10;
        result++;
    }

    return result;
}

inline void remove_from_stdout(unsigned chars)
{
    for(unsigned i = 0; i < chars; i++) {
        std::cout << "\b";
    }
    std::cout << "\033[K";
}