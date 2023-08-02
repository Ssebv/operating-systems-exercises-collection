/********************
 * CLIENT
********************/
// Compile with: gcc -pthread client.c -o client
// Run with: ./client

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_PORT 65000
#define SERVER_ADDR "127.0.0.1"
#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    struct sockaddr_in server_address;
    int sockfd;
    char buffer[BUFFER_SIZE];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_ADDR, &server_address.sin_addr);

    if (connect(sockfd, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
        perror("Error connecting to server");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Connected to server at %s:%d\n", SERVER_ADDR, SERVER_PORT);

    // Here you should implement the LIST functionality
    // Send a message to the server
    // Usage: ./client LIST
    // ./client GET <file_name>
    printf("Please enter the command: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0; // Remove the newline character at the end

    if (send(sockfd, buffer, strlen(buffer), 0) < 0) {
        perror("Error sending message");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Receive response from the server
    printf("Server response:\n");
    while (1) {
        ssize_t received_length = recv(sockfd, buffer, BUFFER_SIZE - 1, 0);
        if (received_length <= 0) {
            break;
        }
        buffer[received_length] = '\0';
        printf("%s", buffer);
    }

    close(sockfd);

    return 0;
}
