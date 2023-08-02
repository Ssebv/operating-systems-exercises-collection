/********************
 * SERVER
********************/
// Compile with: gcc -pthread server.c -o server
// Run with: ./server

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <pthread.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <semaphore.h>

#define NUM_THREADS 10
#define BUFFER_SIZE 1024

int client_sockets[NUM_THREADS];
sem_t mutex;
char buffer[BUFFER_SIZE];

void *handle_client(void *thread_id) {
    int idx = *(int *)thread_id;
    int client_socket = client_sockets[idx];
    static int error_code = 1; // Error code

    // Receive command from the client
    read(client_socket, buffer, sizeof(buffer));

    // Implementing LIST functionality
    if (strncmp(buffer, "LIST", 4) == 0) {
        DIR *d;
        struct dirent *dir;
        d = opendir(".");
        if (d) {
            while ((dir = readdir(d)) != NULL) {
                snprintf(buffer, sizeof(buffer), "%s\n", dir->d_name);
                if (write(client_socket, buffer, strlen(buffer)) < 0) {
                    perror("Error sending file name");
                    closedir(d);
                    return &error_code;
                }
            }
            closedir(d);
        } else {
            perror("Error opening directory");
            return &error_code;
        }
    // Implementing GET functionality
    } else if (strncmp(buffer, "GET ", 4) == 0) {
        char* file_name = buffer + 4;
        FILE *fp = fopen(file_name, "rb");
        if (fp != NULL) {
            while (1) {
                size_t bytes = fread(buffer, 1, sizeof(buffer), fp);
                if (bytes) {
                    write(client_socket, buffer, bytes);
                } else {
                    break;
                }
            }
            fclose(fp);
        } else {
            perror("Error opening file");
            return &error_code;
        }
    }

    close(client_socket);
    free(thread_id);
    return NULL;
}

int main(int argc, char *argv[]) {
    sem_init(&mutex, 0, 1);
    pthread_t threads[NUM_THREADS];
    int our_socket;
    struct sockaddr_in server, client;
    socklen_t len = sizeof(struct sockaddr_in);

    our_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (our_socket == -1) { 
        perror ("ERROR: Unable to create socket.");
        exit (1);
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(65000); // Port
    server.sin_addr.s_addr = INADDR_ANY;

    if (bind(our_socket, (struct sockaddr *)&server, sizeof(server)) == -1) {
        close(our_socket);
        perror("ERROR: Unable to bind socket.");
        exit(1);
    }

    if (listen(our_socket, NUM_THREADS) == -1) {
        perror ("ERROR: Unable to listen on socket.");
        exit(1);
    }

    printf("Server started. Waiting for clients...\n");
    // Create a thread for each client
    for (int i = 0; i < NUM_THREADS; i++) {
        int *idx = malloc(sizeof(*idx));
        *idx = i;

        client_sockets[i] = accept(our_socket, (struct sockaddr *)&client, &len);
        pthread_create(&threads[i], NULL, handle_client, idx);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    close(our_socket);
    return 0;
}
