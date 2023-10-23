#include <iostream>
#include <pthread.h>

#define n 10

// First thread: compute the sum of the first n natural numbers
void* numbers_sum(void* arg) {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += i;
    }
    std::cout << "Sum of the numbers from 1 to " << n << ": " << sum << std::endl;
    pthread_exit(0); // Exit the thread with a return code of 0 (success).
    return NULL; // This line is not necessary after pthread_exit.
}

// Second thread: compute the product of the first n natural numbers
void* numbers_product(void* arg) {
    int product = 1;
    for (int i = 1; i <= n; i++) {
        product *= i;
    }
    std::cout << "Product of the numbers from 1 to " << n << ": " << product << std::endl;
    pthread_exit(0); // Exit the thread with a return code of 0 (success).
    return NULL; // This line is not necessary after pthread_exit.
}

// Third thread: compute the average of the first n natural numbers
void* numbers_average(void* arg) {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += i;
    }
    double avg = static_cast<double>(sum) / n;
    std::cout << "Average of the numbers from 1 to " << n << ": " << avg << std::endl;
    pthread_exit(0); // Exit the thread with a return code of 0 (success).
    return NULL; // This line is not necessary after pthread_exit.
}

/**
 * @brief This program demonstrates the use of pthreads to perform three different operations on an array of numbers.
 * 
 * The program creates three threads, each of which performs a different operation on the array of numbers.
 * The first thread calculates the sum of the numbers, the second thread calculates the product of the numbers,
 * and the third thread calculates the average of the numbers.
 * 
 * The main function creates the threads and waits for them to complete using pthread_join.
 * 
 * @return int 
 */
int main() {
    pthread_t id1, id2, id3;

    pthread_create(&id1, NULL, numbers_sum,(void*) "Sum Thread"); // Create the first thread for sum calculation.
    pthread_create(&id2, NULL, numbers_product,(void*) "Product Thread"); // Create the second thread for product calculation.
    pthread_create(&id3, NULL, numbers_average,(void*) "Average Thread"); // Create the third thread for average calculation.

    pthread_join(id1, NULL); // Wait for the first thread to finish.
    pthread_join(id2, NULL); // Wait for the second thread to finish.
    pthread_join(id3, NULL); // Wait for the third thread to finish.

    return 0;
}
