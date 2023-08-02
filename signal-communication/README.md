
## Signal Sender and Receiver

This repository contains two C source code files demonstrating signal sending and receiving using the `sigqueue` function in C.

### Files:

1. **signal_sender.c**: This file allows the user to input the PID of the receiver and sends signals with multiplication response values to the specified PID using `sigqueue`. It enters into an infinite loop, prompting the user for new multiplication responses, and continuously sends signals until the program is terminated.

2. **signal_receiver.c**: This file is intended to be run as the receiver. It handles the incoming signals sent by the "signal_sender" program and extracts the multiplication response values from the signals. It prints the received responses along with the PID of the sender.

### Compilation:

To compile each C file, you can use the following command:

```sh
gcc -o signal_sender signal_sender.c
gcc -o signal_receiver signal_receiver.c
```

### Usage:

1. Run the "signal_receiver" program first to start listening for signals:

```sh
./signal_receiver
```

2. Then, run the "signal_sender" program to send signals:

```sh
./signal_sender
```

3. The "signal_sender" program will prompt you to enter the PID of the receiver and the multiplication response value to send as a signal.

### Notes:

- The "signal_sender" program enters a loop and continuously sends signals with the provided multiplication response values to the specified receiver PID.
- The "signal_receiver" program listens for incoming signals and displays the received responses along with the PID of the sender.
- This code is intended for educational purposes and demonstrates how to send and receive signals using `sigqueue` in C.

