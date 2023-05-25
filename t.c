#include <stdio.h>
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

unsigned long long binpow(unsigned long long z){
    unsigned long long c = 1;
    for (int i = 0; i < z; i++){
        c *= 2;
    }
    return c;
}

unsigned long long qcom(unsigned long long a, unsigned long long p){
    if (legender_kv_bitwise(a, p) == -1) return 0;
    //k=r h=q
    unsigned long long k = 0, h = p-1;
    // h & 1 == 0?
    while (h % 2 == 0){
        h >>= 1;
        k += 1;
    }
    unsigned long long b = mod_pow(a, h, p);
    unsigned long long c = 1;
    while (legender_kv_bitwise(c, p) != -1) c += 1;
    //f = c

    unsigned long long f = mod_pow(c, h, p), l = 0;
    if (b != 1){
        unsigned long long m, b1, f1, temp;
        while (b != 1){
            m = 0;
            b1 = mod_pow(b, binpow(m), p);
            while (b1 % p != 1){
                m += 1;
                b1 = mod_pow(b, binpow(m), p);
           }
        temp = binpow(k-m);
        f1 = mod_pow(f, temp, p);
        b = b*f1 % p;
        l = l + temp;
        k = m;
        }
    }
    return mod_pow(a, (h+1)/2 , p) * mod_pow(f, l / 2, p) % p;
    printf("%d %d", k, h);
}

int main()
{
    unsigned long long a, p;
    printf("a, p = ");
    scanf("%d %d", &a, &p);
    printf("%d", qcom(a, p));
    return 0;
}
