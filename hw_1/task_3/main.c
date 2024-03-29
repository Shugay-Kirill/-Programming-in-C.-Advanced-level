#include <stdio.h>
#include <stdint.h>

int main(int argc, char const *argv[])
{
    uint16_t lenth_number;
    uint32_t number, result = 1;
    uint8_t count_zero = 0;
    scanf("%d", &lenth_number);
    for (int i = 0; i < lenth_number; i++)
    {
        scanf("%u", &number);
        
        
        if(number != 0 && result % number == 0)
            result /= number;
        else 
            result *= number; 
    }
    printf("%u", result);
    return 0;
}
