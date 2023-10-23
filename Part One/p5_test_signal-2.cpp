#include <signal.h>
#include <unistd.h>
#include <iostream>

using namespace std;

void func(int sig)
{
    cout << "Received a signal from your program " << sig << endl;
    if (sig == SIGQUIT)
    {
        exit(0); // Exit the program when SIGQUIT is received
    }
}

int main()
{
    struct sigaction sa;
    sa.sa_handler = func;     // Set the function to handle the signal
    sa.sa_flags = 0;          // No flags
    sigemptyset(&sa.sa_mask); // Clear any blocked signals

    // Set the sigaction for SIGINT
    if (sigaction(SIGINT, &sa, NULL) == -1)
    {
        perror("Error setting sigaction for SIGINT");
        return 1;
    }

    // Set the sigaction for SIGQUIT
    if (sigaction(SIGQUIT, &sa, NULL) == -1)
    {
        perror("Error setting sigaction for SIGQUIT");
        return 1;
    }

    // begin the infinite while loop which may only be exited by running ctrl+\ 
    while (1)
    {
        cout << "CSUSB CSE 4600 Operating Systems Fall 2023" << endl;
        sleep(1);
    }
    return 0;
}
