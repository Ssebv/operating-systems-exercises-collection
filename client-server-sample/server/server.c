// gcc server.c -o server
// ./server [port]	

#include <sys/types.h> 
#include <sys/socket.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char buffer[256];

int main(int argc, char *argv[]) {
    struct sockaddr_in server;
    int bytes_read, socket_length, our_socket, connection;

    our_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (our_socket < 0) {
        perror("ERROR: Unable to create a socket.");
        exit(1);
    }

    bzero(&server, sizeof(server));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(atoi(argv[1]));

    if (bind(our_socket, (struct sockaddr *)&server, sizeof(server)) < 0) {
        close(our_socket);
        perror("ERROR: Unable to bind the socket.");
        exit(1);
    }

    if (listen(our_socket, 5) < 0) {
        perror("ERROR: Unable to listen.");
        exit(1);
    }

    socket_length = sizeof(struct sockaddr_in);

    //****************************************************
    /*
     * This is the part where you should work!!!
     */

    // Wait for the client connection
    printf("Server active, waiting for connection...\n");

    connection = accept(our_socket, (struct sockaddr *)&server, &socket_length);

    // Display the client's IP address
    printf("Connection accepted from: %s\n", inet_ntoa(server.sin_addr));

    // Receive the filename that will be received
    char filename[4096];
    bzero(&filename[0], sizeof(filename));
    int filename_len = read(connection, filename, sizeof(filename));

    // Open the file for binary writing
    FILE* fp = fopen(filename, "wb");
    if (!fp) {
        perror("ERROR: Unable to open the file.");
        exit(1);
    }

    // Read the data from the client and write it to the file
    while ((bytes_read = read(connection, buffer, sizeof(buffer))) > 0) {
        fwrite(buffer, 1, bytes_read, fp);
    }

    // Close the file and the connection
    fclose(fp);
    printf("File received.\n");
    close(connection);
    close(our_socket);

    //****************************************************

    return 0;
}
