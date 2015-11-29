//
// Created by rdelfin on 11/28/15.
//

#include <tools-lib/StringUtils.h>
#include "representation-parser/Tweet.h"
#include "representation-parser/Dictionary.h"

Tweet::Tweet() {

}

Tweet::Tweet(std::string tokenizedTweet, Dictionary* dictionary)
    : dict(dictionary)
{
    std::vector<std::string> splitTweet = tl::StringUtils::split(tokenizedTweet, ' ');

    for(std::vector<std::string>::iterator it = splitTweet.begin(); it != splitTweet.end(); ++it)
    {
        tokens.push_back(dict->getEntry(*it));
    }
}

Tweet::~Tweet()
{

}