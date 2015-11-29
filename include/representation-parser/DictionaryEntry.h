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
    DictionaryEntry(std::string pattern, bool isRegex = false);

    bool isEntry(std::string);

    bool inline operator==(const std::string & term) {
        return isEntry(term);
    }

    ~DictionaryEntry();
private:
    std::string pattern;
    bool isRegex;
};

bool inline operator==(const std::string& term, DictionaryEntry& entry) {  return entry == term; }
bool inline operator==(const std::string& term, DictionaryEntry* entry) {  return *entry == term; }
bool inline operator==(DictionaryEntry* entry, const std::string& term) {  return *entry == term; }

#endif //TWITTER_DATA_TOOLS_DICTONARYENTRY_H
