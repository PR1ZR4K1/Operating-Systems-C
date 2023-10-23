#include <sys/types.h>
#include <unistd.h>
#include <iostream>

using namespace std;

int main()
{
    pid_t pid; // process id
    char *message; // pointer to message
    int n; // number of times to print message
    cout << "fork program starting\n";
    pid = fork(); // create a new process
    switch (pid)
    {
    case -1: // fork failed
        cout << "Fork failure!\n";
        return 1;
    case 0: // child process
        message = "This is the child\n";
        n = 5;
        break;
    default: // parent process
        message = "This is the parent\n";
        n = 3;
        break;
    }
    for (int i = 0; i < n; ++i) // print message n times
    {
        cout << message;
        sleep(1); // wait for 1 second
    }

    return 0;
}
