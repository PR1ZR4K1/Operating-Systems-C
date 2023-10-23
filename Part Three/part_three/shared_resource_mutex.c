/*
This program demonstrates the use of mutex to synchronize access to a shared resource.
The shared resource is a variable named shared_resource, which is accessed by two threads.
One thread increments the value of shared_resource, while the other thread decrements it.
The program creates two threads and each thread accesses the shared_resource variable using a mutex lock.
The program then waits for the threads to finish and prints the final value of the shared_resource variable.
*/

#include <stdio.h>
#include <pthread.h>

#define iterations 300000000

long long shared_resource = 0; // shared resource variable
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // mutex lock

void* inc_dec_resource(void* arg){
    int resource_value = *(int *) arg;
    for(int i=0; i < iterations; i++){
        pthread_mutex_lock(&mutex); // Lock the mutex to ensure exclusive access to shared_resource.
        shared_resource += resource_value; // Access the shared resource.
        pthread_mutex_unlock(&mutex); // Unlock the mutex after accessing the shared resource.
    }
    pthread_exit(NULL); // Exit the thread.
}

int main(void){
    pthread_t tid1, tid2;
    int value1 = 1;
    pthread_create(&tid1, NULL, inc_dec_resource, &value1); // Create thread 1 for incrementing shared_resource.
    int value2 = -1;
    pthread_create(&tid2, NULL, inc_dec_resource, &value2); // Create thread 2 for decrementing shared_resource.

    pthread_join(tid1, NULL); // Wait for thread 1 to finish.
    pthread_join(tid2, NULL); // Wait for thread 2 to finish.

    printf("Shared resource value: %lld\n", shared_resource); // Print the final value of the shared resource.
    return 0;
}
