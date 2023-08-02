### Description:

This program demonstrates a simple file transfer mechanism between a client and a server using sockets.

### Usage:

1. Compile the server program:
    ```sh
    gcc server.c -o server
    ```

2. Run the server:
    ```sh
    ./server [port]
    ```

3. Compile the client program:
    ```sh
    gcc client.c -o client
    ```

4. Run the client:
    ```sh
    ./client [ip] [port] [filename]
    ```

### Example:

#### Server:
```sh
$ ./server 65000
Server active, waiting for connection...
Connection accepted from: 127.0.0.1
File received.
```

#### Client:
```sh
$ ./client localhost 65000 test.txt
Connecting...
Sending test.txt...
File sent.
```

### Notes:

- Replace `[port]` with the desired port number for the server to listen on.
- Replace `[ip]` with the server's IP address (e.g., "localhost" for local testing).
- Replace `[filename]` with the name of the file you want to transfer.
- Make sure to have the server and client programs compiled before running.
- The server waits for an incoming connection from the client to receive the file.
- The client connects to the server and sends the specified file.
