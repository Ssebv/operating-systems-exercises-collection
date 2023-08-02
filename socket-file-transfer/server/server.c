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

#define NUM_THREADS 10
int connections[NUM_THREADS];
char buffer[256];
sem_t critical_section;

void handle_connection(void *thread_index)
{
	int idx = *(int *)thread_index;
	int i, repeat;

	char filename[4096];
	bzero(&filename[0], sizeof(filename));
	int filename_len = read(connections[idx], filename, sizeof(filename));

	sprintf(filename, "%s");
	FILE *fp = fopen(filename, "wb");
	if (!fp)
	{
		perror("ERROR: Cannot open the file.");
		exit(1);
	}
	else
	{
		printf("Success");
	}

	int bytes_read;
	while ((bytes_read = read(connections[idx], buffer, sizeof(buffer))) > 0)
	{
		fwrite(buffer, 1, bytes_read, fp);
	}

	fclose(fp);
	printf("File received.\n");
	close(connections[idx]);
	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	// Structures and variables for the server
	struct sockaddr_in server;
	int length_read, length_socket, our_socket, connection;
	int destination;

	// Structures and variables for threads and semaphores
	pthread_t threads[NUM_THREADS];
	int idx = 0;
	sem_init(&critical_section, 0, 1);

	// Prepare Server Socket
	our_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (our_socket < 0)
	{
		perror("ERROR: Cannot create socket.");
		exit(1);
	}
	bzero(&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(atoi(argv[1]));
	if (bind(our_socket, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		close(our_socket);
		perror("ERROR: Cannot bind socket.");
		exit(1);
	}
	if (listen(our_socket, 5) < 0)
	{
		perror("ERROR: Cannot listen.");
		exit(1);
	}

	length_socket = sizeof(struct sockaddr_in);

	/****************************************************
	 * This is the part where you need to work on!!!
	 */

	while (1)
	{
		/* Wait for and accept connection */
		printf("Server active, waiting for connection... %d\n", idx);
		/* If a connection arrives, store the connection id in an array */
		connections[idx] = accept(our_socket, (struct sockaddr *)&server, &length_socket);
		printf("Connection accepted from: %s\n", inet_ntoa(server.sin_addr));

		/* Create a thread to handle the connection, pass the connection index in the array (idx) */
		pthread_create(&threads[idx], NULL, handle_connection, (void *)&idx);
		idx++;
	}

	close(our_socket);

	/****************************************************/

	return 0;
}
