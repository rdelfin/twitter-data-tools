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

    void insertRegex(std::string pattern, std::string name);
    DictionaryEntry* getEntry(std::string);

    const DictionaryEntry* entryAt(size_t i) const;

    size_t dictionarySize() const;

    ~Dictionary();
private:
    std::vector<DictionaryEntry*> entries;
};


#endif //TWITTER_DATA_TOOLS_DICTONARY_H
