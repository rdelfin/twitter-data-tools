/*
 * Created by Ricardo Delfin Garcia on 11/24/15.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <representation-parser/Dictionary.h>
#include <representation-parser/DictionaryEntry.h>
#include <representation-parser/Tweet.h>
#include <representation-parser/TweetLoader.h>

inline unsigned num_len(unsigned n);
inline void remove_from_stdout(unsigned chars);

int main(int argc, char* argv[]) {

    /* Get the current working directory, where the config directory should be located */

    // TODO: Move these declarations into a json config file... Or something.
    /* Define paths for the tokenize script as well as the data. These are at constant locations */
    std::string dataPath = "/config/twitter-data/training.1600000.processed.noemoticon.csv";

    std::cout << "Starting..." << std::endl;

    Dictionary dict;

    // Regex for handles
    dict.insertRegex("^@[\\w]+$", "TWITTER_HANDLE_TOK");
    // Regex for... url's?
    dict.insertRegex("^((http|https):\\/\\/)?(www.)?[\\w-_]+(\\.[\\w-_]+){1,3}((\\/)|(\\/[\\w-_]+\\/?)+|((\\/[\\w-_]+)*\\/[\\w-_]+\\.[\\w-_]+))?$", "URL_TOK");
    // Regex for hashtags (probably should not be here)
    dict.insertRegex("^#\\w+$", "HASHTAG_TOK");

    TweetLoader tl(dataPath, &dict);
    tl.load();
    tl.parse();

    std::cout << "Unique terms:" << std::endl << std::endl;

    for(size_t i = 0; i < dict.dictionarySize(); i++) {
        std::cout << dict.entryAt(i)->getName() << std::endl;
    }

    std::cout << "----------------------------" << std::endl;
    std::cout << "Number of unique terms in dictionary: " << dict.dictionarySize() << std::endl;

    std::cout << "Done!" << std::endl;
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