#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// Declaration of global variables to handle scores
int player_1_score = 0;
int player_2_score = 0;
int correct_answer = 0;

static pid_t player_1_pid = 0;
static pid_t player_2_pid = 0;
static int player = 2;

// Function defined to handle the SIGUSR1 signal
void signal_handler_usr(int signum, siginfo_t *info, void *context) {
    //printf("Signal number: %d\n", signum);
    //printf("Sender PID: %d\n", info->si_pid);
    //printf("Additional info: %d\n", info->si_value.sival_int);

    if (info->si_pid != player_1_pid && info->si_pid != player_2_pid) {
        //printf("Player has changed!\n");
        if (player == 1) {
            player = 2;
            player_1_pid = player_2_pid;
            player_2_pid = info->si_pid;
        } else {
            player = 1;
            player_2_pid = player_1_pid;
            player_1_pid = info->si_pid;
        }
    }

    int player_answer = info->si_value.sival_int; // info->si_value.sival_int is the value sent by sigqueue

    if (player_answer == correct_answer) {
        printf("Correct answer from player %d\n", player);
        if (player == 1) {
            player_1_score += 1;
        } else if (player == 2) {
            player_2_score += 1;
        }
    } else {
        printf("Incorrect answer from player %d\n", player);
        if (player == 1) {
            player_1_score -= 1;
        } else if (player == 2) {
            player_2_score -= 1;
        }
    }

    int num1 = rand() % 10 + 1; // Generates random numbers
    int num2 = rand() % 10 + 1;
    correct_answer = num1 * num2;
    printf("Multiplication: %d x %d\n", num1, num2);
}

// Function defined to handle the SIGINT signal
void signal_handler_ctrl(int signum) {
    printf("\nPlayer 1 Score: %d\n", player_1_score);
    printf("Player 2 Score: %d\n", player_2_score);

    player_1_score = 0;
    player_2_score = 0;
}

int main() {
    struct sigaction ctrl_signal, usr_signal; // Structures to define signals

    // Configure signal for SIGINT
    ctrl_signal.sa_handler = signal_handler_ctrl; // Indicate the handler (function)
    ctrl_signal.sa_flags = SA_RESETHAND;
    sigemptyset(&ctrl_signal.sa_mask); // Reset the signal

    // Configure signal for SIGUSR1
    usr_signal.sa_flags = SA_SIGINFO;
    usr_signal.sa_sigaction = signal_handler_usr; // Indicate the handler (function)
    sigemptyset(&usr_signal.sa_mask); // Reset the signal

    sigaction(SIGUSR1, &usr_signal, NULL); // Configure the process with a new handler for SIGUSR1 signal
    sigaction(SIGINT, &ctrl_signal, NULL); // Configure the process with a new handler for SIGINT signal

    int num1, num2;
    while (1) {
        num1 = rand() % 10 + 1; // Generates random numbers
        num2 = rand() % 10 + 1;
        correct_answer = num1 * num2;
        printf("Multiplication: %d x %d\n", num1, num2);
        sleep(2);
    }
    return 0;
}
