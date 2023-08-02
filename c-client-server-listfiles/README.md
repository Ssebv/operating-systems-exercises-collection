
### 1. Client-Server Application

#### client.c
This program (`client.c`) represents the client side of a client-server application. It establishes a connection to the server using TCP sockets and sends an integer value as input to the server. The server responds with a series of messages based on the input it receives. The client is designed to run interactively, and the user can provide an integer value as the input.

#### server.c
This program (`server.c`) represents the server side of the client-server application. It listens for incoming connections from multiple clients and handles them concurrently using threads. Each client connection is assigned a dedicated thread to process its input and send back the response. The server calculates a sequence of messages based on the integer value received from the client.

### 2. List Files

#### list_files.c
This program (`list_files.c`) lists all the files and directories present in the current directory. It uses the `opendir`, `readdir`, and `closedir` functions to read the contents of the directory and prints the names of all the entries.

### How to Compile and Run

To compile each C program, use the `gcc` compiler:

```bash
gcc -o client client.c
gcc -o server server.c -lpthread
gcc -o list_files list_files.c
```

To run the client and server applications, use the following commands:

#### Client-Server Application:

1. Run the server first (specify the port number):
   ```
   ./server [port]
   ```

2. Run the client with the server IP address and port number as arguments:
   ```
   ./client [server_ip] [server_port]
   ```

3. The client will prompt you to enter an integer value. The server will respond with a series of messages based on the input.

#### List Files:

Simply run the `list_files` program to list all the files and directories in the current directory:

```
./list_files
```

