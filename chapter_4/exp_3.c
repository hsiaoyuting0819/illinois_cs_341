#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// not sure why terminal print "signaled!" without aborting the program

void handler(int signum) {
    write(1, "signaled!", 9);
}

int main(int argc, char** argv)
{
    signal(SIGINT, handler);  // simple user-defined handler
    while(1);
    return 0;
}
