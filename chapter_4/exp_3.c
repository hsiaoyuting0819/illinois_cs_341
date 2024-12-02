#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handler(int signum) {
    write(1, "signaled!", 9);
    exit(0);
}

int main(int argc, char** argv)
{
    signal(SIGINT, handler);  // simple user-defined handler
    while(1);
    return 0;
}
