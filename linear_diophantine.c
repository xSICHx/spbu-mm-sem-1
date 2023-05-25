#include <stdio.h>
#include <math.h>
int euclid_extended(long a, long b, long *x, long *y)
{
    long q, r, x1, x0, y1, y0, d, a1, b1;
    a1 = a;
    b1 = b;
    if (b1 == 0)
    {
        d = a1;
        *x = 1;
        *y = 0;
        return 0;
    }
    x0 = 1;
    x1 = 0;
    y0 = 0;
    y1 = 1;
    while (b1 > 0)
    {
        q = a1 / b1;
        r = a1 - q * b1;
        *x = x0 - q * x1;
        *y = y0 - q * y1;
        a1 = b1;
        b1 = r;
        x0 = x1;
        x1 = *x;
        y0 = y1;
        y1 = *y;
    }
    d = a1, *x = x0, *y = y0;
    return d;
}

int linear_diophantine(const long *a, long *x, long n, long b){
    long gcd, temp, tempnod;
    gcd = euclid_extended(abs(a[0]), abs(a[1]), &x[0], &x[1]);
    if (a[0] < 0){
        x[0] *= -1;
    }
    if (a[1] < 0){
        x[1] *= -1;
    }
    for (int i = 2; i < n; i++){
        tempnod = gcd;
        gcd = euclid_extended(tempnod, a[i], &temp, &x[i]);
        //temp1 = temp;
        if (a[i] < 0){
            x[i] *= -1;
        }
        for (int j = 0; j < i; j++){
            x[j] *= temp;
        }
    }
    if (b % gcd == 0){
        for (int i = 0; i < n; i++){
            x[i] *= b / gcd;
            //printf("%d ", x[i]);
        }
    }
    else
        return 1;
    return 0;
}


int main()
{
    long n, i, b;
    scanf("%d", &n);
    long a[n], x[n];
    for (i=0; i < n; i++){
        scanf("%d", &a[i]);
    }
    scanf("%d", &b);
    linear_diophantine(a, x, n, b);
    for(int i = 0; i < n; ++i) {
        printf("%d ",x[i]);
    }
    return 0;
}
