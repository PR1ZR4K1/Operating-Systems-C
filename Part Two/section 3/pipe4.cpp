#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Missing input string. Please provide the input string when running the executable" << endl;
        return 1;
    }
    
    const char *toConcatenate = "! Welcome to CSE 4600 Operating Systems course";
    int fd[2];
    
    if (pipe(fd) == -1) {
        cerr << "Pipe failed" << endl;
        return 1;
    }
    
    // Create a child process to read from the pipe
    pid_t pid = fork();
    
    if (pid < 0) {
        cerr << "Fork failed" << endl;
        return 1;
    }

    // Child process
    if (pid == 0) {
        close(fd[1]); // Closes write
        char buffer[128];
        read(fd[0], buffer, sizeof(buffer)); // Read from pipe
        cout << buffer << toConcatenate << endl;
        close(fd[0]); // Closes read
    }
    
    // Parent process
    else {
        close(fd[0]); // Closes read
        write(fd[1], argv[1], strlen(argv[1])); // Write to pipe
        close(fd[1]); // Close write
        wait(NULL); // Wait for child to finish
    }

    return 0;
}
