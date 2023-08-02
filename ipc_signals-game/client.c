#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int destination_pid;
    printf("Enter the PID of the receiver: ");
    scanf("%d", &destination_pid);

    union sigval additional_value;
    
    while(1) {
        int response;
        printf("Enter a multiplication answer: ");
        scanf("%d", &response);
        
        additional_value.sival_int = response;
        sigqueue(destination_pid, SIGUSR1, additional_value);
        printf("Signal sent\n");
    }
    return 0;
}
