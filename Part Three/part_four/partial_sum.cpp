#include <stdio.h>
#include <pthread.h>

#define SIZE 48
#define NUM_THREADS 4

int array[SIZE];

typedef struct {
    int start;
    int end;
    int result;
} ThreadData;

// Function to calculate the sum of a portion of the array.
int partial_sum(int start, int end) {
    int sum = 0;
    for (int i = start; i < end; i++) {
        sum += array[i];
    }
    return sum;
}

// Function executed by each thread.
void* thread_func(void* arg) {
    ThreadData* data = (ThreadData*) arg;
    data->result = partial_sum(data->start, data->end);
    printf("Partial sum is: %d\n", data->result);
    return NULL;
}

// Main function
int main() {
    // Fill the array with numbers from 1 to SIZE.
    for (int i = 0; i < SIZE; i++) {
        array[i] = i + 1; // Fill the array with numbers from 1 to SIZE.
    }

    int segment_size = SIZE / NUM_THREADS; // Calculate the segment size for each thread.
    pthread_t threads[NUM_THREADS]; // Declare an array of threads.
    ThreadData thread_data[NUM_THREADS]; // Declare an array of thread data.

    // Create threads and assign them their respective segment of the array.
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].start = i * segment_size; // Assign the start index of the segment.
        thread_data[i].end = thread_data[i].start + segment_size; // Assign the end index of the segment.

        // Create the thread and check for errors.
        if (pthread_create(&threads[i], NULL, thread_func, &thread_data[i]) != 0) {
            perror("pthread_create failed"); // Print an error message if pthread_create fails.
            return 1; // Exit the program with an error code.
        }
    }

    int total_sum = 0; // Declare a variable to store the total sum.

    // Wait for all threads to finish and accumulate their results.
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL); // Wait for the thread to finish.
        total_sum += thread_data[i].result; // Accumulate the result of the thread.
    }

    printf("Total sum: %d\n", total_sum); // Print the total sum.
    return 0; // Exit the program with a success code.
}
