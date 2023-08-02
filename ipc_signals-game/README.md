
This repository contains two C programs that demonstrate interprocess communication using signals. The programs simulate a simple multiplayer game where players have to answer multiplication questions.

### `server.c`

This program acts as the server and handles the game logic. It uses signals to receive answers from players and calculates their scores. The server runs an infinite loop, generating random multiplication questions and waiting for players' answers. The server keeps track of the scores for each player and displays the results when interrupted with SIGINT (Ctrl+C).

#### Compilation and Execution:

```bash
gcc server.c -o server
./server
```

### `client.c`

This program acts as the client and allows players to participate in the game. Players can enter their answers for the multiplication questions. The client takes the PID of the server process as a command-line argument to send the answers using signals.

#### Compilation and Execution:

```bash
gcc client.c -o client
./client [server_PID]
```

Replace `[server_PID]` with the PID of the server process.

### How to Play:

1. Run the `server` program.
2. Note down the PID of the `server` process displayed in the terminal.
3. Run multiple instances of the `client` program and provide the `server_PID` as an argument.
4. Players will be prompted to enter their answers for the multiplication questions displayed by the server.
5. The server will indicate whether the answer is correct or incorrect and keep track of each player's score.
6. Press `Ctrl+C` to stop the server and view the final scores of the players.
