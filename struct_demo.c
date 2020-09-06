#include <stdlib.h>
#include <stdio.h>

#pragma pack(1)
typedef struct{
    uint8_t a;
    uint8_t b;
    uint8_t c;
    uint16_t d;
    uint32_t e;
} s_a;

typedef struct{
    uint8_t a;
    uint8_t b;
    uint16_t c;
    uint16_t g;
    uint16_t d;
    uint8_t gd;
    uint32_t e;
} s_b;
#pragma pack()

int main()
{
    s_a a;
    s_b b;
    printf("sizeof:%lu ,%lu\n", sizeof(a), sizeof(b));
}