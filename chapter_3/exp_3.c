#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int length;
    char c_str[0];  // points to the end of the struct, using no memory space
} string;

int main()
{
    const char* text = "person";
    int length = strlen(text);

    string* s_ptr;
    s_ptr = malloc(sizeof(string) + length + 1);
    s_ptr->length = length;
    strcpy(s_ptr->c_str, text);

    free(s_ptr);

    return 0;
}
