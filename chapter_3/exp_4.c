#include <stdio.h>

int main() {
    char* s_ptr_1 = "Share same addr";
    char* s_ptr_2 = "Share same addr";
    char arr_1[] = "Do not share same addr";
    char arr_2[] = "Do not share same addr";

    printf("addr of s_ptr_1: %p\n", s_ptr_1);  // 0x608078370004
    printf("addr of s_ptr_2: %p\n", s_ptr_2);  // 0x608078370004
    printf("addr of arr_1: %p\n", arr_1);  // 0x7ffec3607cf0
    printf("addr of arr_2: %p\n", arr_2);  // 0x7ffec3607d10
    return 0;
}
