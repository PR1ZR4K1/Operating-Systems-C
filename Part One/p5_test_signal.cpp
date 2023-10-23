#include <signal.h>
#include <unistd.h>
#include <iostream>

using namespace std;

void func(int sig)
{
    cout << "Received a signal from your program " << sig << endl;
}

int main()
{
    (void)signal(SIGINT, func); // catch terminal interrupts

    while (1)
    {
        cout << "CSUSB CSE 4600 Operating Systems Fall 2023" << endl;
        sleep(1);
    }
    return 0;
}
