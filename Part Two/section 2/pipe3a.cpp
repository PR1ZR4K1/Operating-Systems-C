#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int nbytes;
    int fd[2]; //file descriptors for pipe
    char buffer[BUFSIZ+1];
    memset(buffer, 0, sizeof(buffer)); //clear buffer

    // Converts arguments to integers and find their sum
    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[2]);
    int sum = num1 + num2;
    
    // Converts sum to string to send through pipe
    char s[BUFSIZ];
    snprintf(s, BUFSIZ, "%d", sum);

    if (pipe(fd) == 0) { //create a pipe
        cout << "Sent the numbers " << num1 << " and " << num2 << " to pipe for their summation." << endl;
        nbytes = write(fd[1], s, strlen(s)); //send sum to pipe
        nbytes = read(fd[0], buffer, BUFSIZ); //read sum from pipe
        cout << "The sum of the two numbers is: " << buffer << endl;
        return 0;
    }
    return 1;
}
