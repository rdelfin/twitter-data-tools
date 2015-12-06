/*
 * Created by Ricardo Delfin Garcia on 11/28/15.
 */

#include "representation-parser/Dictionary.h"
#include "representation-parser/DictionaryEntry.h"

#include <algorithm>

#include <iostream>

//void deleteEntry(DictionaryEntry* entry) { delete entry; }

Dictionary::Dictionary() {

}

void Dictionary::insertRegex(std::string pattern, std::string name) {
    entries.push_back(new DictionaryEntry(pattern, name));
    regexEntries.push_back(entries[entries.size() - 1]);
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
        entries.push_back(new DictionaryEntry(term));
        idxMap.insert({{term, entries.size() - 1}});
        return entries[entries.size() - 1];
    }
}

const DictionaryEntry* Dictionary::entryAt(size_t i) const
{
    return i >= dictionarySize() ? nullptr : entries[i];
}

int64_t Dictionary::getIndex(DictionaryEntry* entry) const {
    for(size_t i = 0; i < entries.size(); i++) {
        if(entries[i] == entry) {
            return i;
        }
    }

    return -1;
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
    //std::for_each(entries.begin(), entries.end(), deleteEntry);
}