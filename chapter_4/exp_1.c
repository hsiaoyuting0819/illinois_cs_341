#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    printf("Double Print!!! ");  // not flushed before fork
    pid_t id = fork();
    if (id == -1) exit(1);
    if (id > 0) {
        // parent process
        pid_t parent_id = getpid();
        printf("Parent Process!!! Parent PID:%d Child PID:%d\n", parent_id, id);
        // <terminal>: Double Print!!! Parent Process!!! Parent PID:4927 Child PID:4931
    } else {
        // child process
        pid_t parent_id = getppid();
        pid_t child_id = getpid();
        printf("Child Process!!! Parent PID:%d Child PID:%d\n", parent_id, child_id);
        // <terminal>: Double Print!!! Child Process!!! Parent PID:4927 Child PID:4931
    }

    return 0;
}
