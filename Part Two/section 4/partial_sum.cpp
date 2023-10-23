#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>

#define SIZE 48
#define NUM_PROCESSES 4

int array[SIZE];

int partial_sum(int start, int end) {
    int sum = 0;
    for (int i = start; i < end; i++) {
        sum += array[i];
    }
    return sum;
}

int main() {
    // Fill the array with numbers from 1 to 48.
    for (int i = 0; i < SIZE; i++) {
        array[i] = i + 1;
    }

    int total_sum = 0;
    int segment_size = SIZE / NUM_PROCESSES;

    // Create an array of pipe file descriptors for each child process.
    int pipes[NUM_PROCESSES][2];

    for (int i = 0; i < NUM_PROCESSES; i++) {
        if (pipe(pipes[i]) == -1) {
            std::cerr << "Pipe failed" << std::endl;
            return 1;
        }

        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork failed");
            return 1;
        } else if (pid == 0) { // Child process
            int start = i * segment_size;
            int end = start + segment_size;
            int partialResult = partial_sum(start, end);
            printf("Partial sum is: %d\n", partialResult);

            // Close the read end of the pipe for this child.
            close(pipes[i][0]);

            // Write the partial result to the write end of the pipe for this child.
            write(pipes[i][1], &partialResult, sizeof(partialResult));

            // Close the write end of the pipe for this child.
            close(pipes[i][1]);

            return 0;
        }
    }

    // Parent waits for all children and collects results.
    for (int i = 0; i < NUM_PROCESSES; i++) {
        int status;
        pid_t pid = wait(&status);
        if (WIFEXITED(status)) {
            int partialResult;
            // Read the partial result from the read end of the pipe for this child.
            read(pipes[i][0], &partialResult, sizeof(partialResult));
            total_sum += partialResult;
        }
        // Close the read end of the pipe for this child.
        close(pipes[i][0]);
    }

    printf("Total sum: %d\n", total_sum);
    return 0;
}
