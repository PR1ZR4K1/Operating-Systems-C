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

int main() {
    char *message = (char *) malloc(100);
    strcpy(message, "You are in the main function!\n"); // Initialize the message in the main function.
    pthread_t tid1;
    pthread_create(&tid1, NULL, &thread_func, message); // Create a new thread and pass the message.

    printf("%s", message); // Print the message from the main function.
    pthread_join(tid1, NULL); // Wait for the thread to finish.

    return 0;
}
