#include <stdio.h>
#include <unistd.h>

int main()
{
    int value = fork(); // create a child process and store the returned value in the variable 'value'

    if (value == 0)
    {
        // printf("Child pid: %d", getpid()); 
                   // if the returned value is 0, then this is the child process
        fork(); // create another child process
        if (getpid() % 2 == 0)
        {           // if the current process ID is even, then create another child process
            fork(); // create another child process
        }
    }
    else
    {
        fork(); // if the returned value is not 0, then this is the parent process, so create another child process
    }

    printf("Hello from PID: %d, PPID: %d\n", getpid(), getppid()); // print the process ID and parent process ID
    sleep(2);                                                      // sleep for 2 seconds maybe to make sure no other processes are still running
    return 0;                                                      // exit the program
}
