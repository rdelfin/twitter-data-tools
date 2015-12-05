//
// Created by rdelfin on 12/5/15.
//

#include "representation-parser/Configuration.h"


#include <fstream>
#include <unistd.h>


Configuration::Configuration()
    : Configuration("/config/config.json") {
}

Configuration::Configuration(std::string file) {
    std::ifstream configFile(file);
    configFile >> data;

    char buffer[1024];
    getcwd(buffer, sizeof(buffer));
    cwd = std::string(buffer);
}

std::string Configuration::dataFile() {
    return cwd + data["data"];
}

std::string Configuration::output() {
    return cwd + data["output_folder"];
}

std::string Configuration::tokenizer() {
    return cwd + data["tokenizer"];
}

Configuration* Configuration::instance() {
    if(_instance == nullptr) {
        _instance = new Configuration;
    }

    return _instance;
}

