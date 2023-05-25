#include <stdio.h>

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

int  chinese_rem(int a[], int m[], int *x, int n){
    int fi0, fi1, t, M, gcd;
    gcd = euclid_extended(m[0], -m[1], &fi0, &fi1);
    if ((a[1]- a[0]) % gcd != 0)
        return 0;
    fi0 *= (a[1] - a[0]) / gcd;
    t = m[0]*fi0 + a[0];
    M = m[0]*m[1]/gcd;
    for (int i = 2; i != n; i++){
        gcd = euclid_extended(M, -m[i], &fi0, &fi1);
        if ((a[i] - t) % gcd != 0)
            return 0;
        fi0*= (a[i] - t)/gcd;
        t = M*fi0 + t;
        M = M * m[i] / gcd;
    }
    return (t % M + M) % M;

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
