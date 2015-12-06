/*
 * Created by Ricardo Delfin Garcia on 11/28/15.
 */

#include <regex>
#include "representation-parser/DictionaryEntry.h"
#include "tools-lib/StringUtils.h"

DictionaryEntry::DictionaryEntry() { }

DictionaryEntry::DictionaryEntry(std::string term, size_t idx)
    : pattern(term), isRegex(false), name(term), idx(idx) { }

DictionaryEntry::DictionaryEntry(std::string pattern, std::string name, size_t idx)
    : pattern(pattern), isRegex(true), name(name), idx(idx) { }


bool DictionaryEntry::isEntry(std::string s) {
    if(isRegex) {
        std::regex reg(pattern);
        bool result = std::regex_match(s, reg);
        return result;
    }
    else {
        return tl::StringUtils::trim(s) == pattern;
    }
}

DictionaryEntry::~DictionaryEntry() { }