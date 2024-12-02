#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

// undefined behavior due to file not prepared

int main()
{
    size_t buf_cap = 0;
    char* buf = NULL;
    ssize_t nread;
    FILE* file = fopen("test.txt", "r");
    int cnt = 0;
    while (cnt < 5 && (nread = getline(&buf, &buf_cap, file)) != -1) {
        ++cnt;
        printf("%s", buf);
        if (fork() == 0) {
            exit(0);
        }
        wait(NULL);
    }
    return 0;
}
