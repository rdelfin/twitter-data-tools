/*
 * Created by Ricardo Delfin Garcia on 11/28/15.
 */

#include <regex>
#include "representation-parser/DictionaryEntry.h"
#include "tools-lib/StringUtils.h"

DictionaryEntry::DictionaryEntry() { }

DictionaryEntry::DictionaryEntry(std::string pattern, bool isRegex)
    : pattern(pattern), isRegex(isRegex) { }


bool DictionaryEntry::isEntry(std::string s) {
    if(isRegex) {
        std::regex reg(pattern);
        return std::regex_match(s, reg);
    }
    else {
        return tl::StringUtils::trim(s) == pattern;
    }
}

DictionaryEntry::~DictionaryEntry() { }