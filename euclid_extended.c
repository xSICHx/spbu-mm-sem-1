#include <stdio.h>
#include <math.h>
long euclid_extended(long a, long b, long *x, long *y)
{
    long q, r, x1, x0, y1, y0, fa = 0, fb = 0;
    if (a < 0)
        fa = 1;
    if (b < 0)
        fb = 1;
    a = abs(a);
    b = abs(b);
    if (b == 0)
    {
        *x = 1, *y = 0;
        return a;
    }
    x0 = 1;
    x1 = 0;
    y0 = 0;
    y1 = 1;
    while (b > 0)
    {
        q = a / b;
        r = a - q * b;
        *x = x0 - q * x1;
        *y = y0 - q * y1;
        a = b;
        b = r;
        x0 = x1;
        x1 = *x;
        y0 = y1;
        y1 = *y;
        //printf("q= %d x01= %d %d y01= %d %d \n", q, x0, x1, y0, y1);
    }
    *x = x0;
    if (fa == 1)
        *x *= -1;
    *y = y0;
    if (fb == 1)
        *y *= -1;
    return a;
}

long mod_inv(long a, long b)
 {
     long x, y, nod;
     nod = euclid_extended(a, b, &x, &y);
     if (nod == 1){
         x%=b;
         return x>0 ? x : x+b;
     } else return 0;
 }
int main()
{
    long a, b;
    scanf("%d %d", &a, &b);
    long d, x, y;
    d = euclid_extended(a, b, &x, &y);
    printf("x = %d y = %d d = %d\n", x, y, d);
    long inv = mod_inv(a, b);
    printf("inv %d mod %d = %d", a, b, inv);
    return 0;
}
