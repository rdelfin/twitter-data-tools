/*
 * Created by Ricardo Delfin Garcia on 11/24/15.
 */

#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
    std::ifstream file("config/twitter-data/tweets-text.txt", std::ifstream::in);

    std::string output;
    getline(file, output);

    std::cout << "First tweet: " << std::endl << output << std::endl << std::endl;
    std::cout << "I don't know what to believe anymore" << std::endl;
}