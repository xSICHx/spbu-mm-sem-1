#include <stdio.h>
int fib_pow(unsigned long n, int m)
    {
        int a[50000];
        a[0] = 0;
        a[1] = 1;
        int i = 1;
        while (i != n)
        {
            a[i+1] = (a[i]+a[i-1])%m;
            i += 1;
            if (a[i-1]==0 && a[i]==1)
                break;
        }
        printf("%d\n", i);
        for (int j = 0; j <= i; j++)
        {
            printf("%d ", a[j]);
        }
        printf("\n");
        return a[n % (i - 1)];
    }


int main()
{
    unsigned long a;
    int b;
    scanf("%d%d", &a, &b);
    printf("%d", fib_pow(a, b));
    return 0;
}
