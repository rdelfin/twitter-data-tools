/*
 * Created by Ricardo Delfin Garcia on 11/24/15.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <representation-parser/Dictionary.h>
#include <tools-lib/StringUtils.h>
#include <representation-parser/Tweet.h>

#include "tools-lib/Process.h"

int main(int argc, char* argv[]) {

    /* Get the current working directory, where the config directory should be located */
    char cwd[512];
    getcwd(cwd, sizeof(cwd));

    // TODO: Move these declarations into a json config file... Or something.
    /* Define paths for the tokenize script as well as the data. These are at constant locations */
    std::string scriptPath(cwd), dataPath(cwd);
    scriptPath += "/config/ark-tweet-nlp-0.3.2/twokenize.sh";
    dataPath += "/config/twitter-data/tweets-text.txt";

    // Runs the twokenize script with the default shell.
    tl::Process p("/bin/sh", {scriptPath, dataPath});

    // Start the program and wait (no input).
    p.start();
    p.wait();

    // Get the output and parse data
    std::stringstream& ss = p.stdout();

    Dictionary dictionary;

    std::vector<Tweet> tweets;

    std::string line;
    while(std::getline(ss, line)) {
        std::vector<std::string> tweet = tl::StringUtils::split(line, '\t');
        tweets.push_back(Tweet(tweet[0], &dictionary));
    }

    std::cout << "Number of terms in dictionary: " << dictionary.dictionarySize() << std::endl;
}