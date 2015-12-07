/*
 * Created by Ricardo Delfin Garcia on 11/28/15.
 */

#ifndef TWITTER_DATA_TOOLS_DICTONARYENTRY_H
#define TWITTER_DATA_TOOLS_DICTONARYENTRY_H

#include <string>

class DictionaryEntry
{
public:
    DictionaryEntry();
    DictionaryEntry(std::string term, size_t idx);
    DictionaryEntry(std::string pattern,  std::string name, size_t idx);

    bool isEntry(std::string);

    bool inline operator==(const std::string & term) {
        return isEntry(term);
    }

    const std::string& getName() const { return name; }
    bool getIsRegex() const { return isRegex; }
    size_t getIdx() const { return idx; }

    ~DictionaryEntry();
private:
    std::string pattern;
    std::string name;
    bool isRegex;
    size_t idx;
};

bool inline operator==(const std::string& term, DictionaryEntry& entry) {  return entry == term; }
bool inline operator==(const std::string& term, DictionaryEntry* entry) {  return *entry == term; }
bool inline operator==(DictionaryEntry* entry, const std::string& term) {  return *entry == term; }

#endif //TWITTER_DATA_TOOLS_DICTONARYENTRY_H
