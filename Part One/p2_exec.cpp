#include <unistd.h>
#include <iostream>

using namespace std;

int main()
{
    cout << "Running ps with execlp\n";

    int i = 0;

    pid_t pid = fork();

    if (pid == 0)
    {
        i = 1;
        execlp("ls", "ls", "-l", NULL);
        
    }

    while (i == 1)
    {
        pid = fork();

        if (pid == 0)
        {
            execlp("echo", "echo", "Hello from CSUSB CSE 4600 Section 03 Fall 2023", NULL);
        }
    }

    // pid = fork();

    // if (pid == 0)
    // {
    //     execlp("cat", "cat", "p2_exec.cpp", NULL);
    // }

    // pid = fork();

    // if (pid == 0)
    // {
    //     execlp("touch", "touch", "", NULL);
    // }

    return 0;
}