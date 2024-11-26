#include <stdio.h>
#include <stdint.h>

union pixel {
    struct {
        char red;
        char blue;
        char green;
        char alpha;
    } values;
    uint32_t encoded;
};

int main()
{
    union pixel a;
    a.values.red = 0x1;
    a.values.blue = 0x2;
    a.values.green = 0x3;
    a.values.alpha = 0x4;
    printf("%#010x\n", a.encoded);  // 0x04030201 => current machine is little endian ?
    printf("%p\n", &a.values.red);  // 0x7ffe96ab2e64
    printf("%p\n", &a.values.alpha);  // 0x7ffe96ab2e67
    printf("%p\n", &a.encoded);  // 0x7ffe96ab2e64
    return 0;
}
