#include <stdio.h>

int euclid(int a,int b) {
    while (a!=b){
        if (a > b){
            a %= b;
        }
        else {
            b %= a;
        }
    }
    return a;
}

int euclid_recursive(int a, int b)
{
    if (a > b)
    {
        a %= b;
    }
    else
    {
        b %= a;
    }
    if (a == b)
    {
        return a;
    }
    else
    {
        return euclid_recursive(a, b);
    }
}

int main()
{
    int a, b, c;
    scanf("%d %d", &a, &b);
    c = euclid_recursive(a, b);
    printf("%d", c);
    return 0;
}
