//
// Created by rdelfin on 12/5/15.
//

#ifndef TWITTER_DATA_TOOLS_CONFIGURATION_H
#define TWITTER_DATA_TOOLS_CONFIGURATION_H

#include <string>
#include <json/json.hpp>

using json = nlohmann::json;

class Configuration {
public:
    Configuration();
    Configuration(std::string file);

    std::string dataFile();
    std::string tokenizer();
    std::string output();

    size_t threads();
    size_t taskSize();

    static Configuration* instance();
private:
    json data;
    std::string cwd;

    static Configuration* _instance;

    std::string joinPath(std::string);
};


#endif //TWITTER_DATA_TOOLS_CONFIGURATION_H
