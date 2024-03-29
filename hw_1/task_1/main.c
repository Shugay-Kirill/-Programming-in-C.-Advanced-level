#include <stdio.h>
#include <limits.h>

int main(int argc, char const *argv[])
{
    int lenth_number, number, count = 0, max = INT_MIN;
    scanf("%d", &lenth_number);
    for (int i = 0; i < lenth_number; i++)
    {
        scanf("%d", &number);
        if (max < number)
        {
            max = number;
            count = 1;
        }
        else if (max == number)
        {
            count++;
        }
    }
    printf("%d", count);


    return 0;
}
