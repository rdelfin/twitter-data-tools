/*
 * Created by Ricardo Delfin Garcia on 11/28/15.
 */

#include "representation-parser/Dictionary.h"
#include "representation-parser/DictionaryEntry.h"

#include <algorithm>

#include <iostream>

void deleteEntry(DictionaryEntry* entry) { delete entry; }

Dictionary::Dictionary() {

}

void Dictionary::insertRegex(std::string pattern, std::string name) {
    DictionaryEntry *entry = new DictionaryEntry(pattern, name);
    entries.push_back(entry);
    regexEntries.push_back(entry);
}

DictionaryEntry* Dictionary::getEntry(std::string term) {
    // Search over regexes first
    DictionaryEntry* found = foundRegex(term);

    // If it is found in the regexes, return
    if(found != nullptr) {
        return found;
    }
    // Otherwise, search in the hash map (keys must be unique).
    else if(idxMap.count(term) > 0) {
        return entries[idxMap.at(term)];
    }
    // If it is found in neither, add the term to the vector of entries and add the index to the map.
    else {
        DictionaryEntry *result = new DictionaryEntry(term);
        entries.push_back(result);
        idxMap.insert({{term, entries.size() - 1}});
        return result;
    }
}

const DictionaryEntry* Dictionary::entryAt(size_t i) const
{
    return i >= dictionarySize() ? nullptr : entries[i];
}

size_t Dictionary::dictionarySize() const {
    return entries.size();
}

DictionaryEntry* Dictionary::foundRegex(std::string term)
{
    for(size_t i = 0; i < regexEntries.size(); i++) {
        if(regexEntries[i]->isEntry(term)) {
            return regexEntries[i];
        }
    }

    return nullptr;
}

Dictionary::~Dictionary() {
    std::for_each(entries.begin(), entries.end(), deleteEntry);
}