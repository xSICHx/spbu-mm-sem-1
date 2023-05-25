#include <stdio.h>

long euclid_extended(long a, long b, long *x, long *y)
{
    long q, r, x1, x0, y1, y0;
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
    }
    *x = x0;
    *y = y0;
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

int  chinese_rem(int a[], int m[], int *x, int n){
    long M = 1;
    int sm = 0;
    for (int i = 0; i != n; i++){
        M *= m[i];
    }
    for (int i = 0; i != n; i++){
        sm += a[i]*mod_inv(M/m[i], m[i]) * (M/m[i]);
    }
    return (sm % M + M) % M;
}

int main()
{

    int n, i, x;
    printf("n: ");
    scanf("%d", &n);
    long a[n], m[n];
    printf("a: ");
    for (i=0; i < n; i++){
        scanf("%d", &a[i]);
    }
    printf("m: ");
    for (i=0; i < n; i++){
        scanf("%d", &m[i]);
    }
    printf("%d", chinese_rem(&a, &m, &x, n));
    return 0;
}
