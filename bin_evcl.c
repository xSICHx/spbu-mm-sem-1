#include <stdio.h>

int bin_euclid_recursive(int a, int b)
{
    if (a == 0)
    {
        return b;
    }
    if (b == 0)
    {
        return a;
    }
    while (a % 2 != 1)
    {
        a = a / 2;
    }
    while (b % 2 != 1)
    {
        b = b / 2;
    }

    if (a > b)
    {
        a -= b;
    }
    else
    {
        b -= a;
    }

    return bin_euclid_recursive(a, b);
}

int euclid_binary(int a, int b)
{
    int k = 0;
    while ((a&1!=1) && (b&1!=1))
    {
        a >>= 1;
        b >>= 1;
        k ++;
    }
    int c = bin_euclid_recursive(a, b);
    return c<<k;
}

int main()
{
    int a, b;
    scanf("%d %d", &a, &b);
    printf("GCD(%d, %d) = %d", a, b, euclid_binary(a, b));
    return 0;
}
