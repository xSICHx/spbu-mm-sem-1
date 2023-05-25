#include <stdio.h>
int mod_pow(long x, long y, long m){
        long pr=1;
        if (y&1)
            pr *= x;
        y >>= 1;
        while (y !=0){
            x = x*x % m;
            if (y&1)
                pr *= x;
                pr %= m;
            y >>= 1;
        }
        return pr % m;
    }

long rec_mod_pow(long x, long y, long m){
    if (y == 0)
        return 1;
    x = x % m;
    int temp = rec_mod_pow(x, y >> 1, m);
    if (y&1)
        return (((temp*temp)%m)*x)%m;
    else
        return (temp*temp)%m;
}

int main() {
    long a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    printf("%d %d",mod_pow(a, b, c), rec_mod_pow(a, b, c));
    return 0;
}
