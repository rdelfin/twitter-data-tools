/*
 * Created by Ricardo Delfin Garcia on 11/28/15.
 */

#include "representation-parser/Dictionary.h"
#include "representation-parser/DictionaryEntry.h"

#include <algorithm>

void deleteEntry(DictionaryEntry* entry) { delete entry; }

Dictionary::Dictionary() {

}

void Dictionary::insertRegex(std::string pattern) {
    entries.push_back(new DictionaryEntry(pattern, true));
}

DictionaryEntry* Dictionary::getEntry(std::string term) {
    std::vector<DictionaryEntry*>::iterator itResult = std::find(entries.begin(), entries.end(), term);

    if(itResult != entries.end()) {
        return *itResult;
    }
    else {
        DictionaryEntry *result = new DictionaryEntry(term, false);
        entries.push_back(result);
        return result;
    }
}

size_t Dictionary::dictionarySize() {
    return entries.size();
}

Dictionary::~Dictionary() {
    std::for_each(entries.begin(), entries.end(), deleteEntry);
}