// gcc client.c -o client
// ./client [ip] [port] [filename]
// ip : localhost
// filename : file.txt

#include <sys/types.h>
#include <sys/socket.h> 
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char buffer[256];

int main(int argc, char *argv[]) {
    int 	connection, bytes_read;
    struct sockaddr_in client;
    struct hostent *host_ip, *gethostbyname();

    memset(&client, 0, sizeof(client));

    client.sin_family = AF_INET;
    client.sin_port = htons(atoi(argv[2]));

    if (isdigit(argv[1][0]))
        client.sin_addr.s_addr = inet_addr(argv[1]);
    else {
        host_ip = gethostbyname(argv[1]);
        if (host_ip == NULL) {
            perror (("ERROR: Unable to resolve the hostname %s.", argv[1]));
            exit(1);
        }
        memcpy(&client.sin_addr, host_ip->h_addr, host_ip->h_length);
    }

    connection = socket(AF_INET, SOCK_STREAM, 0);
    if (connection < 0) {
        perror("ERROR: Unable to create a socket");
        exit(1);
    }

    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[2]));
    server.sin_addr.s_addr = INADDR_ANY;

    connect(connection, (struct sockaddr *)&server, sizeof(server));

    printf("Connecting...\n");

    //***********************************************************
    /*
     * This is the part where you should work !!!
    */
    printf("Sending %s...\n", argv[3]);

    int file = open(argv[3], O_RDONLY);
    if (file < 0) {
        perror("ERROR: Unable to open the file.");
        exit(1);
    }

    char buffer[256];
    while ((bytes_read = read(file, buffer, sizeof(buffer))) > 0) {
        write(connection, buffer, bytes_read);
    }
    close(file);

    printf("File sent.\n");
    close(connection);
    //***********************************************************

    return 0;
}
