//pipe1a

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    FILE *fpi; //for reading a pipe
    char buffer[BUFSIZ+1]; //BUFSIZ defined in <stdio.h>
    int chars_read;
    memset(buffer, 0, sizeof(buffer)); //clear buffer

    char command[256];  // buffer
    strcpy(command, argv[1]); // copies argument 1


    // combines arguments into one strings
    for (int i = 2; i < argc; ++i) {
        strcat(command, " ");
        strcat(command, argv[i]);
    }

    fpi = popen(command, "r");  // pipe to enter "command"
    if (fpi != NULL) {
        // reads data from pipe into buffer
        chars_read = fread(buffer, sizeof(char), BUFSIZ, fpi);
        if (chars_read > 0) {
            cout << "Output from pipe: " << buffer << endl;
        }
        pclose(fpi); // close the pipe
        return 0;
    }
    return 1;
}
