/********************
 * CLIENT
********************/

#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 256

int main(int argc, char *argv[])
{
    int numero;

    // Structures and variables for the client
    int connection, bytes_read;
    struct sockaddr_in client;
    struct hostent *host_ip;
    char buffer[BUFFER_SIZE]; // Add buffer here
    bzero(&client, sizeof(client));
    client.sin_family = AF_INET;
    client.sin_port = htons(atoi(argv[2]));
    client.sin_addr.s_addr = inet_addr(argv[1]);

    // Prepare connection
    connection = socket(AF_INET, SOCK_STREAM, 0);
    if (connection < 0)
    {
        perror("ERROR: Unable to create the socket");
        exit(1);
    }

    //***********************************************************
    /*
     * This is the part where you should work on!
    */
    if (connect(connection, (struct sockaddr *)&client, sizeof(client)) < 0)
    {
        perror("ERROR: Unable to connect to the server");
        close(connection);
        exit(1);
    }

    printf("Sending %s...\n", argv[3]);

    int file = open(argv[3], O_RDONLY);
    if (file < 0)
    {
        perror("ERROR: Unable to open the file.");
        close(connection);
        exit(1);
    }

    while ((bytes_read = read(file, buffer, sizeof(buffer))) > 0)
    {
        write(connection, buffer, bytes_read);
    }

    close(file);
    printf("File sent.\n");
    close(connection);

    //***********************************************************
    return 0;
}
