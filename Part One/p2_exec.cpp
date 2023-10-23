#include <unistd.h>
#include <iostream>
#include <sys/wait.h>

using namespace std;

int main()
{
    cout << "Listing current directory with ls -l\n\n";

    // create a child process
    // child_pid = 0 | mother_pid = actual pid of the child process
    pid_t pid = fork();

    // ensure child process will execute the following
    if (pid == 0)
    {
        execlp("ls", "ls", "-l", NULL);
        }

    // wait unil the child process has completed its operation before allowing mother process to continue
    wait(NULL);
    cout << "\n";
    // create new child process
    pid = fork();

    if (pid == 0)
    {
        execlp("echo", "echo", "Hello from CSUSB CSE 4600 Section 03 Fall 2023", NULL);
    }

    // wait unil the child process has completed its operation before allowing mother process to continue
    wait(NULL);
    cout << "\n";
    pid = fork();

    if (pid == 0)
    {
        execlp("cat", "cat", "p2_exec.cpp", NULL);
    }

    // wait unil the child process has completed its operation before allowing mother process to continue
    wait(NULL);
    cout << "\nDeleting that file";
    pid = fork();

    if (pid == 0)
    {
        execlp("rm", "rm", "./test.txt", NULL);
    }

    return 0;
}