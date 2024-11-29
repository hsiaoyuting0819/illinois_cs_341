#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

// <terminal>: 3:d
// <terminal>: 2:c
// <terminal>: 1:b
// <terminal>: 0:a

void test(int argc, char** argv) {
    int status;
    pid_t id;
    while (--argc && (id = fork())) {
        waitpid(id, &status, 0);
    }
    printf("%d:%c\n", argc, (*argv)[argc]);
}

int main(int argc, char** argv)
{
    char* arr = "abcd";
    int arr_size = strlen(arr);
    test(arr_size, &arr);
    return 0;
}
