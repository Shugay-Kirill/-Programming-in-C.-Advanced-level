#include <stdio.h>

6 2

c2^6= n!/(k!*(n-k)!) = 5*6/2! = 15


int binom(int n, int k)
{
    double res = 1;
    for (int i = 1; i <= (n - k); i++)
    {
        res *= (n - i + 1);
        res /= i;
    }
    return (int)(res + 0.001);
}

int main()
{
    int n, k;
    scanf("%d%d", &n, &k);
    printf("%d", binom(n, k));
    return 0;
}
