/*
 pthreads_message_demo.cpp
 A very simple example demonstrating the usage of pthreads.
 Compile: g++ -o pthreads_message _demo pthreads_demo.cpp -lpthread
 Execute: ./pthreads_message _demo
*/

#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <cstring>
#include <string>

void *thread_func(void *arg) {
    char *message = (char *) arg;
    strcpy(message, "You are in thread function!\n");
    return NULL;
}

/**
 * @brief This program demonstrates the use of pthreads to create a child thread that prints a message.
 * 
 * The main function creates a message, creates a child thread using pthread_create, and waits for the child thread to complete using pthread_join.
 * The message is printed after the child thread completes.
 * 
 * @return int Returns 0 on successful execution.
 */
int main() {
    char *message = (char*)malloc(100);
    strcpy(message, "You are in the main function!\n");
    pthread_t tid1;
    pthread_create(&tid1, NULL, &thread_func, message);
    pthread_join(tid1, NULL);  // Ensure the child thread completes before printing.
    printf("%s", message);
    return 0;
}
