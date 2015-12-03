/*
 * Created by Ricardo Delfin Garcia on 11/25/15.
 * Code partially obtained from Eike Rathke:
 */

/*
 * This program illustrates how to use the pipe(), fork(), dup2() and exec()
 * system calls to control stdin and stdout of an exec'ed program via pipes
 * from within the calling program.
 *
 * Just because someone asked me ;-)
 * Eike Rathke
 * Tue Jun 26 21:44:17 CEST 2001
 */

#include "tools-lib/Process.h"

#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <thread>
#include <fcntl.h>

namespace tl
{
    Process::Process(const std::string& executable, const std::vector<std::string>& argv)
        : executable(executable), argv(argv) {

    }

    void Process::start() {
        pid_t nPid;

        if(pipe(pipe_in) != 0)
        {
            perror("pipe() in");
            exit(255);
        }

        if(pipe(pipe_out) != 0)
        {
            perror("pipe() out");
            exit(255);
        }

        /* Fork this program to create the process. */
        nPid = fork();
        if(nPid < 0)
        {
            /* There was an error. Exit. */
            perror("fork() 1");
            exit(255);
        }
        else if (nPid == 0)
        {
            /* This is the child process. Setup pipe, stdin, stdout appropriately. */

            /* dup pipe read/write to stdin/stdout */
            dup2(pipe_in[0], STDIN_FILENO);
            dup2(pipe_out[1], STDOUT_FILENO);

            /* close unnecessary pipe descriptors for a clean environment */
            close(pipe_in[0]);
            close(pipe_in[1]);
            close(pipe_out[0]);
            close(pipe_out[1]);

            /* Send STDERR_FILENO to /dev/null */
            int devNullFd = open("/dev/null", O_WRONLY);
            dup2(devNullFd, STDERR_FILENO);
            close(devNullFd);

            /* Convert string vector to char array vector */
            std::vector<const char*> argvector;
            argvector.push_back(executable.c_str());
            for(std::vector<std::string>::const_iterator it = argv.begin();
                 it != argv.end();
                 ++it) {
                argvector.push_back(it->c_str());
            }
            argvector.push_back(nullptr);

            // Execute the program, with the exacutable included
            execv(executable.c_str(), (char **)&argvector[0]);

            /* Should only execute on error. */
            perror("execlp()");
            exit(255);
        }
        else
        {
            /* Save PID into global file. Wait for the user to make use of stdin, and call wait */
            pid = nPid;

            /* Close unused pipes */
            close(pipe_in[0]);
            close(pipe_out[1]);
        }
    }


    void Process::wait() {
        writeStdin();

        std::thread reader(&Process::readStdout, this);

        int status;
        if (waitpid(pid, &status, 0) == -1)
        {
            perror("waitpid()");
            exit(255);
        }

        reader.join();
    }

    void Process::writeStdin() {
        FILE *stream;
        if ((stream = fdopen(pipe_in[1], "a")) == NULL)
        {
            perror("fdopen() w");
            exit(255);
        }

        // Obtain input stream data
        std::string input = in_stream.str();

        // Clear out string buffer
        in_stream.clear();
        in_stream.str(std::string());

        // Write out to pipe
        fputs(input.c_str(), stream);
        fclose(stream);
    }

    void Process::readStdout() {
        FILE *stream;
        int ch;
        if ((stream = fdopen(pipe_out[0], "r")) == NULL)
        {
            perror("fdopen() r");
            exit(255);
        }

        /* Read all characters into out_stream */
        while ((ch = getc(stream)) != EOF)
            out_stream.put((char)ch);

        /* CLose the file stream */
        fclose(stream);
    }


    std::stringstream& Process::stdout() {
        return out_stream;
    }


    std::stringstream& Process::stdin() {
        return in_stream;
    }

    Process::~Process() {

    }
}