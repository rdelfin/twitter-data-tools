/*
 * Created by Ricardo Delfin Garcia on 11/28/15.
 */

#ifndef TWITTER_DATA_TOOLS_STRINGUTILS_H
#define TWITTER_DATA_TOOLS_STRINGUTILS_H

#include <string>

namespace tl {
    class StringUtils {
    public:
        static std::string &trim(std::string &s);

    private:
        static std::string &ltrim(std::string &s);

        static std::string &rtrim(std::string &s);
    };
}


#endif //TWITTER_DATA_TOOLS_STRINGUTILS_H
