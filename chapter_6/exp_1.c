#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Two points to remember
// 1. Calling fork() under multiple threads,
// the child process only has a single thread,
// which is a clone of the thread that called fork().
// 2. Avoid creating threads before forking,
// since the others threads are immediately terminated when forking,
// which may lead to unexpected errors or deadlocks.

static pid_t child = -2;

void* func(void* arg) {
    printf("(%d) %s starting up...\n", getpid(), (char*)arg);
    while (child == -2) sleep(1);
    printf("(%d) %s finishing...\n", getpid(), (char*)arg);
    return NULL;
}

int main() {
    pthread_t id_1, id_2;
    pthread_create(&id_1, NULL, func, "thread one");
    pthread_create(&id_2, NULL, func, "thread two");

    child = fork();
    printf("(%d) %s\n", getpid(), "forking complete");
    sleep(2);
    printf("(%d) %s\n", getpid(), "main thread finished");
    pthread_exit(NULL);
    return 0;
}
