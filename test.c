#include <stdio.h>
unsigned long long binpow(unsigned long long z){
    unsigned long long c = 1;
    for (int i = 0; i < z; i++){
        c *= 2;
    }
    return c;
}
int main()
{
    unsigned long n = 6;
    printf("%d", binpow(n));
    return 0;
}
