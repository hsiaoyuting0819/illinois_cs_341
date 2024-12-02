#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

// Signal handlers are inherited and changeable.

void handleOne(int sig_num) {
    pid_t id = getpid();
    printf("(pid:%d) handleOne signaled:%d!!!\n", id, sig_num);
    exit(0);
}

void handleTwo(int sig_num) {
    pid_t id = getpid();
    printf("(pid:%d) handleTwo signaled:%d!!!\n", id, sig_num);
    exit(0);
}

int main() {
    signal(SIGINT, handleOne);

    pid_t id = fork();
    if (id == 0) {
        signal(SIGINT, handleTwo);
        while(1);
    } else {
        wait(NULL);
    }
    return 0;
}
