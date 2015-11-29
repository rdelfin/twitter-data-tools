//
// Created by rdelfin on 11/28/15.
//

#ifndef TWITTER_DATA_TOOLS_DICTONARY_H
#define TWITTER_DATA_TOOLS_DICTONARY_H

#include <string>
#include <vector>

class DictionaryEntry;

class Dictionary {
public:
    Dictionary();

    void insertRegex(std::string);
    DictionaryEntry* getEntry(std::string);

    size_t dictionarySize();

    ~Dictionary();
private:
    std::vector<DictionaryEntry*> entries;
};


#endif //TWITTER_DATA_TOOLS_DICTONARY_H
