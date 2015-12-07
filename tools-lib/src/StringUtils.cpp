/*
 * Created by Ricardo Delfin Garcia on 11/28/15.
 *
 * References:
 *   String split methods obtained from: http://stackoverflow.com/questions/236129/split-a-string-in-c
 *   String trim methods obtains from: http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
 */

#include "tools-lib/StringUtils.h"

#include <algorithm>
#include <locale>
#include <sstream>

namespace tl {

    // trim from start
    std::string& StringUtils::ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
    }

    // trim from end
    std::string& StringUtils::rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
    }

    // trim from both ends
    std::string& StringUtils::trim(std::string &s) {
        return ltrim(rtrim(s));
    }


    std::vector<std::string>& StringUtils::split(const std::string &s, char delim, std::vector<std::string> &elems) {
        std::stringstream ss(s);
        std::string item;
        while (std::getline(ss, item, delim)) {
            elems.push_back(item);
        }
        return elems;
    }


    std::vector<std::string> StringUtils::split(const std::string &s, char delim) {
        std::vector<std::string> elems;
        StringUtils::split(s, delim, elems);
        return elems;
    }
}