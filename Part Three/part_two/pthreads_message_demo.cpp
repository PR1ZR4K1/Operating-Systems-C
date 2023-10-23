/*
pthreads_message_demo.cpp
A very simple example demonstrating the usage of pthreads.
Compile: g++ -o pthreads_message_demo pthreads_message_demo.cpp -lpthread
Execute: ./pthreads_message_demo
*/

#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <cstring>
#include <string>

void *thread_func(void *arg) {
    char *message = (char *) arg;
    strcpy(message, "You are in thread function!\n"); // Modify the message in the thread.
    return NULL;
}

/**
 * @brief This program demonstrates the use of pthreads to create a child thread that modifies a message.
 * 
 * The main function creates a message, creates a child thread using pthread_create, and waits for the child thread to complete using pthread_join.
 * The message is modified in the child thread and printed after the child thread completes.
 * 
 * @return int Returns 0 on successful execution.
 */
int main() {
    char *message = (char *) malloc(100);
    strcpy(message, "You are in the main function!\n"); // Initialize the message in the main function.
    pthread_t tid1;
    pthread_create(&tid1, NULL, &thread_func, message); // Create a new thread and pass the message.
    pthread_join(tid1, NULL);  // Wait for the child thread to complete before proceeding.
    printf("%s", message); // Print the modified message.
    return 0;
}
