/*

  Demonstration of using threads and semaphores with lpthread and gcc

*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>


sem_t semaphore;

void Hello(void *idx)
{
    int j;
    while (1) {
        sem_wait(&semaphore);
        for (j = 0; j < 10; j++){
            printf("Hello %d\t%d\n", idx, j);
            sleep(rand() % 2);
        };
        sem_post(&semaphore);
    }
    pthread_exit(NULL); // When a thread needs to terminate
}

int main(int argc, char *argv[])
{
    sem_init(&semaphore, 0, 1);

    pthread_t thread_list[3];
    int i, ret;
    for (i = 0; i < 3; i++)
    {
        ret = pthread_create(&thread_list[i], NULL, (void *)Hello, (void *)i);
    };
    for (i = 0; i < 3; i++) {
        pthread_join(thread_list[i], NULL);
    }
}
