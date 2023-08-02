/*
Compilation code: gcc -pthread -o thread [filename]
*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
   
sem_t semaphore;
sem_t semaphore2;

int counter = 0; // Global variable to manage the total counter

void process(void *idx) // Function that each thread will execute
{ 
	long int j;
	int local_counter = 0; // Local variable to manage each thread's local counter

	while (1) {
		for (j = 0; j < 10; j++) {
			sem_wait(&semaphore);
			if (local_counter < 10) {
				local_counter++;
			}
			sem_post(&semaphore);
			if (local_counter == 10) {
				sem_wait(&semaphore2);
				counter += local_counter;
				local_counter = 0;
				sem_post(&semaphore2);
			}
			sem_post(&semaphore);
		}
		printf("Thread %ld has finished\n", (long)idx);
		pthread_exit(NULL);
	}	
}

int main(int argc, char *argv[])
{
	sem_init(&semaphore, 0, 1); // Initialize semaphore with value 1 (available) and 0 (not available)
	sem_init(&semaphore2, 0, 1); // Semaphore to ensure only one thread accesses the global counter

	pthread_t thread_list[50];
	int ret;
	long int i;
	for (i = 0; i < 50; i++) {
		ret = pthread_create(&thread_list[i], NULL, (void *)&process, (void *)(i));
	}
	for (i = 0; i < 50; i++) {
		pthread_join(thread_list[i], NULL);
	}
	printf("Total increments: %d\n", counter);
    if (counter == 500) {
        printf("The hypothesis holds true\n");
    } else {
        printf("The hypothesis does not hold true\n");
    }	
}
/* 
The hypothesis holds true since the counter reaches 500 due to the 10 iterations of each thread (TOTAL 50). However, improvements could be made 
to allow each thread to run independently. Currently, multiple threads run simultaneously due to the use of two semaphores.
By adding a third semaphore in the first conditional of the process function, each thread could be made to run independently.
Alternatively, a nested loop could be added inside the first for loop of the process function to achieve independent execution for each thread.
*/
