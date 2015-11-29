/*
 * Created by Ricardo Delfin Garcia on 11/28/15.
 */

#ifndef TWITTER_DATA_TOOLS_STRINGUTILS_H
#define TWITTER_DATA_TOOLS_STRINGUTILS_H

#include <string>
#include <vector>

namespace tl {
    class StringUtils {
    public:
        static std::string &trim(std::string &s);
        static std::vector<std::string>& split(const std::string &s, char delim, std::vector<std::string> &elems);
        static std::vector<std::string> split(const std::string &s, char delim);
    private:
        static std::string &ltrim(std::string &s);

        static std::string &rtrim(std::string &s);
    };
}


#endif //TWITTER_DATA_TOOLS_STRINGUTILS_H
