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
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

char buffer[256];

int main(int argc, char *argv[])
{
    int number;

    // Client structures and variables
    int 	connection, bytes_read;
    struct  sockaddr_in client;
    struct  hostent 	*host_ip, *gethostbyname();

    // Initialize client socket address
    bzero(&client, sizeof(client));
    client.sin_family = AF_INET;
    client.sin_port = htons(atoi(argv[2]));
    client.sin_addr.s_addr = inet_addr(argv[1]);

    // Prepare connection
    connection = socket(AF_INET, SOCK_STREAM, 0);
    if (connection < 0) { 
        perror ("ERROR: Unable to create socket");
        exit(1);
    }

    //***********************************************************
    /*
     * This is the part where you should work !!!
    */
    connect(connection, (struct  sockaddr *)&client, sizeof(client));

    printf("Enter the number of repetitions (integer): ");
    scanf("%d", &number);
    sprintf(buffer, "%d", number);
    write(connection, buffer, sizeof(buffer));

    bytes_read = read(connection, buffer, sizeof(buffer));
    while (bytes_read > 0) {
        printf("Server's message: %s\n", buffer);
        bytes_read = read(connection, buffer, sizeof(buffer));
    }
    close(connection);
    //***********************************************************
    return 0;
}
