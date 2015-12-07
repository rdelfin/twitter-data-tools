//
// Created by rdelfin on 12/5/15.
//

#include "representation-parser/Configuration.h"

#include <fstream>
#include <unistd.h>

Configuration* Configuration::_instance = nullptr;

Configuration::Configuration()
    : Configuration("/config/config.json") {
}

Configuration::Configuration(std::string file) {
    char buffer[1024];
    getcwd(buffer, sizeof(buffer));
    cwd = std::string(buffer);

    std::ifstream configFile(joinPath(file));
    configFile >> data;
}

std::string Configuration::dataFile() {
    return joinPath(data["data"]);
}

std::string Configuration::output() {
    return joinPath(data["output_folder"]);
}

std::string Configuration::tokenizer() {
    return joinPath(data["tokenizer"]);
}

size_t Configuration::threads() {
    return data["threads"]["max"];
}

size_t Configuration::taskSize() {
    return data["threads"]["task_size"];
}

Configuration* Configuration::instance() {
    if(_instance == nullptr) {
        _instance = new Configuration;
    }

    return _instance;
}

std::string Configuration::joinPath(std::string path) {
    return cwd + path;
}
