#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// Global variables declaration for handling scores
int player1_score = 0;
int player2_score = 0;
int correct_answer = 0;

static pid_t player1_pid = 0;
static pid_t player2_pid = 0;
static int current_player = 2;

// Function defined to handle the SIGUSR1 signal
void signal_handler_usr(int signum, siginfo_t *info, void *context) {
    if (info->si_pid != player1_pid && info->si_pid != player2_pid) {
        if (current_player == 1) {
            current_player = 2;
            player1_pid = player2_pid;
            player2_pid = info->si_pid;
        } else {
            current_player = 1;
            player2_pid = player1_pid;
            player1_pid = info->si_pid;
        }
    }

    int player_answer = info->si_value.sival_int;

    if (player_answer == correct_answer) {
        printf("Correct answer from player %d\n", current_player);
        if (current_player == 1) {
            player1_score += 1;
        } else if (current_player == 2) {
            player2_score += 1;
        }
    } else {
        printf("Incorrect answer from player %d\n", current_player);
        if (current_player == 1) {
            player1_score -= 1;
        } else if (current_player == 2) {
            player2_score -= 1;
        }
    }

    int num1 = rand() % 10 + 1; // Generate random numbers
    int num2 = rand() % 10 + 1;
    correct_answer = num1 * num2;
    printf("Multiplication: %d x %d\n", num1, num2);
}

// Function defined to handle the SIGINT signal
void signal_handler_ctrl(int signum) {
    printf("\nPlayer 1 Score: %d\n", player1_score);
    printf("Player 2 Score: %d\n", player2_score);
    
    player1_score = 0;
    player2_score = 0;
}

int main() {
    struct sigaction ctrl_signal, usr_signal; // Structures to define signals
    
    // Configure signal handler for SIGINT
    ctrl_signal.sa_handler = signal_handler_ctrl; // Set the handler (function)
    ctrl_signal.sa_flags = SA_RESETHAND;
    sigemptyset(&ctrl_signal.sa_mask); // Reset the signal

    // Configure signal handler for SIGUSR1
    usr_signal.sa_flags = SA_SIGINFO;
    usr_signal.sa_sigaction = signal_handler_usr; // Set the handler (function)
    sigemptyset(&usr_signal.sa_mask); // Reset the signal

    sigaction(SIGUSR1, &usr_signal, NULL); // Configure the process with a new handler for SIGUSR1 signal
    sigaction(SIGINT, &ctrl_signal, NULL); // Configure the process with a new handler for SIGINT signal
    
    int num1, num2;
    while (1) {
        num1 = rand() % 10 + 1; // Generate random numbers
        num2 = rand() % 10 + 1;
        correct_answer = num1 * num2;
        printf("Multiplication: %d x %d\n", num1, num2);
        sleep(2);
    }
    return 0;
}
