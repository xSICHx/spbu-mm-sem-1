#include <stdio.h>
#include <time.h>

unsigned long long mod_pow(unsigned long long x, unsigned long long y, unsigned long long m)
{
    unsigned long long z = 1;
    while (y > 0)
    {
        if (y&1)
            z = (z * x) % m;
        x = (x*x) % m;
        y >>= 1;
    }
    return z;
}


int legender_euler(unsigned long long a, unsigned long long p)
{
    int c = mod_pow(a, (p-1)/2, p);
    return c > 1 ? c-p : c;
}

int legender_kv_bitwise(unsigned long long a, unsigned long long p)
{
    int c = 1;
    while (a > 1)
    {
        if (a & 1)
        {
            if (a > p)
            {
                a = a % p;
            }
            else
            {
                a += p;
                p = a - p;
                a -= p;
                c *= ((p-1)>>1 & 1 * ((a-1)>>1 & 1)) ? (-1) : 1;
            }
        }
        else
        {
            a >>= 1;
            c *= ((p*p - 1)>>3) & 1 ? (-1) : 1;
        }
    }
    return c;
}

int legender_kv(unsigned long long a, unsigned long long p)
{
    int c = 1;
    while (a > 1)
    {
        if (a & 1)
        {
            if (a > p)
            {
                a = a % p;
            }
            else
            {
                a += p;
                p = a - p;
                a -= p;
                c *= ((p-1)/2 & 1 * ((a-1)/2 & 1)) ? (-1) : 1;
            }
        }
        else
        {
            a >>= 1;
            //((p*p - 1)/8) & 1 ? c*= (-1) : c*= 1;
            if (((p*p - 1)/8) & 1)
            {
                c *= -1;
            }
        }
    }
    return c;
}

int main()
{
    unsigned long long g, z;
    double t1, t2;
    clock_t start, end;
    printf("a, p: ");
    scanf("%d %d", &g, &z);
    start = clock();
    for (int i = 1; i < 10000000; i++){
        legender_euler(g, z);
    }
    end = clock();
    t1 = (double)(end - start) / CLOCKS_PER_SEC;

    start = clock();
    for (int i = 1; i < 10000000; i++){
        legender_kv(g, z);
    }
    end = clock();
    t2 = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%d %d\n %f \n %f", legender_euler(g, z), legender_kv(g, z), t1, t2);
    return 0;
}
