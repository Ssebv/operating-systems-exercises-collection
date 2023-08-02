**Server:**

- **File Name:** server.c
- **Compilation Command:** gcc server.c -o server -pthread
- **Execution Command:** ./server [port]

**Client:**

- **File Name:** client.c
- **Compilation Command:** gcc client.c -o client
- **Execution Command:** ./client [server_IP_address] [port] [file_name]

**List Files:**

- **File Name:** list_files.c
- **Compilation Command:** gcc list_files.c -o list_files
- **Execution Command:** ./list_files

**Description:**

The provided C programs implement a simple server-client file transfer application using sockets. The "Server" program listens for incoming connections and handles multiple client requests simultaneously. It accepts files sent by clients and stores them on the server-side.

**Usage:**

1. **Server:**
   - The server program should be compiled with the pthread library, as it uses multithreading to handle multiple client connections.
   - To compile: `gcc server.c -o server -pthread`
   - To execute: `./server [port]`
   - Replace `[port]` with the port number on which the server should listen for incoming connections.

2. **Client:**
   - The client program is used to send files to the server.
   - To compile: `gcc client.c -o client`
   - To execute: `./client [server_IP_address] [port] [file_name]`
   - Replace `[server_IP_address]` with the IP address of the server, `[port]` with the port number on which the server is listening, and `[file_name]` with the name of the file you want to send to the server.

3. **List Files:**
   - The "List Files" program lists the files present in the current directory of the server.
   - To compile: `gcc list_files.c -o list_files`
   - To execute: `./list_files`

**Note:**

- The server and client must be executed on different terminals or machines, with the server running before the client.
- Make sure to provide valid IP addresses, port numbers, and file names as required by the client program.
- The server will store the received files in its current working directory.
- The provided implementation is a basic example and may not handle all error scenarios. It is recommended to add appropriate error handling and input validation for production use.