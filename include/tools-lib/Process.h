/*
 * Created by Ricardo Delfin on 11/25/15.
 */

#ifndef TWITTER_DATA_TOOLS_PROCESS_H
#define TWITTER_DATA_TOOLS_PROCESS_H

#include <sstream>
#include <vector>
#include <mutex>

namespace tl
{

    class Process {
    public:
        Process(const std::string& executable, const std::vector<std::string>& argv);

        void start();
        void wait();

        std::stringstream& stdout();
        std::stringstream& stdin();

        ~Process();
    private:
        pid_t pid;
        std::string executable;
        std::vector<std::string> argv;
        std::stringstream out_stream;
        std::stringstream in_stream;

        int pipe_in[2];
        int pipe_out[2];

        void writeStdin();
        void readStdout();
    };
}


#endif //TWITTER_DATA_TOOLS_PROCESS_H
