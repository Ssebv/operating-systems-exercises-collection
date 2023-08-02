
File Transfer Client-Server
==================================

Introduction:
--------------
This project consists of a simple file transfer client-server application. The server allows clients to request a list of files in the server directory and download files from the server.

Compilation and Execution:
--------------------------
To compile and run the server, follow these steps:
1. Open a terminal in the server directory.
2. Compile the server code with the following command:
   ```
   gcc -pthread server.c -o server
   ```
3. Run the server using the following command:
   ```
   ./server
   ```

To compile and run the client, follow these steps:
1. Open a terminal in the client directory.
2. Compile the client code with the following command:
   ```
   gcc -pthread client.c -o client
   ```
3. Run the client using the following command:
   ```
   ./client
   ```

Usage:
-------
1. The client can communicate with the server using two commands:
   - `LIST`: To request a list of files available on the server.
   - `GET <file_name>`: To download a specific file from the server. Replace `<file_name>` with the name of the file you want to download.

2. After executing the client, it will prompt you to enter a command. You can enter one of the above commands to interact with the server.

3. The server will respond to the `LIST` command by sending a list of available files. For the `GET` command, the server will send the contents of the requested file to the client.

Note:
------
- This is a basic file transfer application and may not have advanced error handling or security features. Use it in a controlled environment or enhance it for real-world use.
- The server's default port is set to 65000. You can change it by modifying the `SERVER_PORT` macro in the server code.
- The server and client should be executed on the same machine for this example. If you want to run them on different machines, update the `SERVER_ADDR` macro in the client code with the server's IP address.
