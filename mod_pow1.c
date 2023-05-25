#include <stdio.h>

int mod_pow(long x, long y, long m)
{
    long z = 1;
    while (y > 0)
    {
        if (y&1)
            z = (z * x) % m;
        x = (x*x) % m;
        y >>= 1;
    }
    return z;
}

int main()
{
    long a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    printf("%d", mod_pow(a, b, c));
    return 0;
}
