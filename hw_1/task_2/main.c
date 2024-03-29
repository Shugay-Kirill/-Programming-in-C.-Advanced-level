#include <stdio.h>
#include <stdint.h>

int main(int argc, char const *argv[])
{
    uint32_t number;
    scanf("%u", &number);
    printf("%u", (((~(number >> 24)) << 24) | ((number << 8) >> 8)));
    return 0;
}
