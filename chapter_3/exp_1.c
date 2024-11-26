#include <stdio.h>

void foo(const int* i_ptr) {
    printf("%d\n", *i_ptr);
}

int main()
{
    const int i = 7;
    (*((int *)&i)) = 11;  // attempt to fool compiler

    printf("%d\n", i);  // result of C prints 11, while result of C++ prints 7
    foo(&i);  // both results of C and C++ prints 11

    return 0;
}
