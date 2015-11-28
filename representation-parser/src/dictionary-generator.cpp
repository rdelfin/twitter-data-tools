/*
 * Created by Ricardo Delfin Garcia on 11/24/15.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>

#include "tools-lib/Process.h"

int main(int argc, char* argv[]) {
    char cwd[512];
    getcwd(cwd, sizeof(cwd));

    std::string scriptPath(cwd), dataPath(cwd);
    scriptPath += "/config/ark-tweet-nlp-0.3.2/twokenize.sh";
    dataPath += "/config/twitter-data/tweets-text.txt";

    tl::Process p("/bin/sh", {scriptPath, dataPath});

    p.start();
    p.wait();

    std::stringstream& ss = p.stdout();

    std::cout << "This is the data:" << std::endl << std::endl;

    std::string line;
    while(std::getline(ss, line)) {
        std::cout << ">> " << line << std::endl;
    }
}