/********************
 * SERVER
********************/

#include <sys/types.h> 
#include <sys/socket.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_THREADS 10
int connections[NUM_THREADS];
char buffer[256];
sem_t critical_section;

void handle_connection(void *thread_idx)
{
    int idx = (int)((int *)thread_idx);
    int i, repetitions;

    read(connections[idx], buffer, sizeof(buffer));
    repetitions = atoi(buffer);
    for (i = 1; i <= repetitions; i++) {
        sprintf(buffer, "Thread %d, counting %d/%d times\n", idx, i, repetitions);
        printf("%s", buffer);
        write(connections[idx], buffer, sizeof(buffer));
        sleep(1);
    }
    close(connections[idx]);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    // Server structures and variables
    struct sockaddr_in server;
    int bytes_read, server_socket, connection;
    int destination;

    // Thread and semaphore structures and variables
    pthread_t threads[NUM_THREADS];
    int idx = 0;
    sem_init(&critical_section, 0, 1);

    // Prepare Server Socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("ERROR: Unable to create socket.");
        exit(1);
    }
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(atoi(argv[1]));
    if (bind(server_socket, (struct sockaddr *)&server, sizeof(server)) < 0) {
        close(server_socket);
        perror("ERROR: Unable to bind the socket.");
        exit(1);
    }
    if (listen(server_socket, 5) < 0) {
        perror("ERROR: Unable to listen.");
        exit(1);
    }
    int server_socket_length = sizeof(struct sockaddr_in);

    /****************************************************
     * This is the part where you should work!!!
     */

    while (1) {
        /* Wait and accept connection */
        printf("Server active, waiting for connection... %d\n", idx);
        /* If a connection arrives, store the connection id in a vector */
        connections[idx] = accept(server_socket, (struct sockaddr *)&server, &server_socket_length);
        printf("Connection accepted from: %s\n", inet_ntoa(server.sin_addr));

        /* Create a thread to handle the connection, passing the connection's position in the vector (idx) */
        pthread_create(&threads[idx], NULL, (void *)&handle_connection, (void *)idx);
        idx++;
    }
    close(server_socket);

    /****************************************************/

    return 0;
}
