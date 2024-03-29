#include <stdio.h>
#include <stdint.h>

int main(int argc, char const *argv[])
{
    uint16_t step, K = 26;
    scanf("%d", &step);
    char ch;
    while ((ch = getchar()) != '.')
    {
        if (ch != ' ')
        {
            printf("%c", (ch + step % K));
        }
        else
            printf(" ");
    }
    return 0;
}
