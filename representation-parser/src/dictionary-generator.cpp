/*
 * Created by Ricardo Delfin Garcia on 11/24/15.
 */

#include <iostream>
#include <fstream>
#include <sstream>

#include "tools-lib/Process.h"

int main(int argc, char* argv[]) {
    std::ifstream file("config/twitter-data/tweets-text.txt", std::ifstream::in);

    std::string output;
    getline(file, output);

    std::cout << "First tweet: " << std::endl << output << std::endl << std::endl;
    std::cout << "I don't know what to believe anymore" << std::endl;

    tl::Process p("/bin/cat", {"/home/rdelfin/wat.txt"});

    p.start();
    p.wait();

    std::stringstream& ss = p.stdout();
    std::string in;
    ss >> in;
    while (in != "") {
        std::cout << in << std::endl;
        in = "";
        ss >> in;
    }

}