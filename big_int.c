#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(x,y) ((y) > (x) ? (x) : (y))
#define MAX(x,y) ((y) > (x) ? (y) : (x))


typedef struct big_int{
    unsigned int length;
    unsigned char *number;
    unsigned char sgn;
} big_int;


big_int *big_int_get(const char *num_bin){
    big_int *result = malloc(sizeof(big_int));
    int len = strlen(num_bin);
    result->length = (len>>3) + ((len & 7) > 0);// (len % 8 > 0) ? 1 + len/8: len/8;%8
    // деление на 8 + остаток, если есть
    result->number = (char*)malloc(result->length);
    int temp_sum = 0, k = 0, k_res = 0;
    for (int i = len - 1; i >= 0; i--, k++){
        if (k == 8){
            result->number[k_res] = temp_sum;
            k = 0;
            temp_sum = 0;
            k_res++;
        }
        if (num_bin[i] == '1')
            temp_sum |= (1<<k);
    }
    result->number[k_res] = temp_sum;
    return result;
}

void big_int_print(big_int *n){
    int buff[8];
    int j = 0;
    unsigned char temp;
    for (temp = n->number[n->length-1]; temp; temp >>=1, j++)
        buff[j] = temp & 1;
    for (--j; j >= 0; j--){
        printf("%d", buff[j]);
    }
    for (int i = n->length-2; i >= 0; i--) {
        for (j = 7; j >= 0; j--){
            printf("%d", (n->number[i]>>j) & 1);
        }
    }
    printf("\n");
}

void big_int_free(big_int *n){
    free(n->number);
    free(n);
}

void big_int_assign(big_int *n1, const big_int *n2){
    n1->length = n2->length;
    n1->number = realloc(n1->number, n1->length);
    memcpy(n1->number, n2->number, n1->length);
}


big_int *big_int_add(const big_int *n1, const big_int *n2){
    big_int *result = malloc(sizeof(big_int));
    result->length = MAX(n1->length, n2->length);
    result->number = malloc(result->length);
    int rem = 0;
    int i;
    for (i = 0; i < MIN(n1->length, n2->length); i++){
        result->number[i] = ((n1->number[i]+n2->number[i]) & 0xFF) + rem;
        rem = ((n1->number[i] + n2->number[i]) > 0xFF);
    }
    // случай равенства длин чисел n1 и n2
    if (n1->length == n2->length){
        if (rem) {
            result->number = realloc(result->number, result->length + 1);
            result->length++;
            result->number[i] = 1;
        }
        return result;
    }
    // второй цикл нужен, так как при разной длине n1 и n2 после достижения i MIN(n1->length, n2->length)
    // длины в одном из этих двух чисел не будет элементов, соответственно будет
    // непредсказуемый результат
    for (i; i < MAX(n1->length, n2->length); i++){
        result->number[i] = ((n1->length < n2->length ? n2->number[i] : n1->number[i])
                +rem) & 0xFF;
        rem = (((n1->length < n2->length ? n2->number[i] : n1->number[i])
                +rem) > 0xFF);
    }
    if (rem) {
        result->number = realloc(result->number, result->length + 1);
        result->length++;
        result->number[i] = 1;
    }
    return result;
}

big_int *big_int_zero() {
    big_int *result = malloc(sizeof(big_int));
    result->length = 1;
    result->number = malloc(1);
    result->number[0] = 0;
    return result;
}

void big_int_add_to_first(big_int *n1, const big_int *n2){
    big_int *temp = big_int_add(n1, n2);
    big_int_assign(n1, temp);
    big_int_free(temp);
}

int big_int_comp(const big_int *n1, const big_int *n2){ //n1 > n2: 1, n2 < n2: -1, n1 ==n2: 0
    if (n1->length > n2->length)
        return 1;
    else if (n1->length < n2->length)
        return -1;
    else{
        for (int i = n1->length-1; i >= 0; i--){
            if (n1->number[i] > n2->number[i])
                return 1;
            else if (n1->number[i] < n2->number[i])
                return -1;
        }
        return 0;
    }
}

big_int *big_int_minus(const big_int *n1, const big_int *n2){
    big_int *result = big_int_zero();
    if (big_int_comp(n1, n2) == 1){//случай, когда первое число больше второго
        big_int_assign(result, n1);
        int j, i;
        for (i = 0; i < n2->length; i++){
            if (result->number[i] >= n2->number[i])
                result->number[i] -= n2->number[i];
            else{//ищем ненулевой элемент
                j = i + 1;
                while (result->number[j] == 0){
                    result->number[j] = 0xFF;
                    j++;
                }
                result->number[j]--;
                result->number[i] = (1<<8) - (n2->number[i] - result->number[i]);
            }

        }
        // убираем незначащие нули
        i = result->length - 1;
        while (result->number[i] == 0)
            i--;
        result->length = i + 1;
        result->number = realloc(result->number, result->length);
    }
    return result;
}

void big_int_minus_to_first(big_int *n1, const big_int *n2){
    big_int *temp = big_int_minus(n1, n2);
    big_int_assign(n1, temp);
    big_int_free(temp);
}

void *big_int_shift_add(big_int *n){
    n->length++;
    n->number = realloc(n->number, n->length);
    for (int i = n->length-1; i > 0; i--){
        n->number[i] = n->number[i-1];
    }
    n->number[0] = 0;
}

void *big_int_shift_minus(big_int *n){
    for (int i = 0; i < n->length-1; i++){
        n->number[i] = n->number[i+1];
    }
    n->length--;
    n->number = realloc(n->number, n->length);
}

big_int *big_int_multiply(const big_int *n1, const big_int *n2){
    big_int *result = big_int_zero();
    big_int *temp = big_int_zero();
    int i, j;
    for (i = 0; i < n1->length; i++){
        temp->length = 1; temp->number = realloc(temp->number, 1); temp->number[0] = 0;
        for (j = 0; j < n1->number[i]; j++)
            big_int_add_to_first(temp, n2);
        //добавляем нули
        for (j = 0; j < i; j++)
            big_int_shift_add(temp);
        big_int_add_to_first(result, temp);
    }
    big_int_free(temp);
    return result;
}

void big_int_multiply_to_first(big_int *n1, const big_int *n2){
    big_int *temp = big_int_multiply(n1, n2);
    big_int_assign(n1, temp);
    big_int_free(temp);
}

void big_int_print_0x(big_int *m){
    for (int i = 0; i < m->length; i++)
        printf("%d ", m->number[i]);
    printf("\n");
}

big_int *big_int_mod(const big_int *n1, const big_int *n2){
    big_int *result = big_int_zero(); big_int_assign(result, n1);
    if (big_int_comp(result, n2) == -1) {
        return result;
    }
    else{
        while (big_int_comp(result, n2) >= 0) {
            big_int_minus_to_first(result, n2);
        }
        return result;
    }
}

void big_int_mod_to_first(big_int *n1, const big_int *n2){
    big_int *temp = big_int_mod(n1, n2);

    big_int_assign(n1, temp);
    big_int_free(temp);
}

big_int *big_int_div(const big_int *n1, const big_int *n2){
    big_int *result = big_int_zero();
    big_int *e = big_int_zero(); e->number[0] = 1;
    big_int *temp = big_int_zero(); big_int_assign(temp, n1);
    while (big_int_comp(temp, n2) >= 0) {
        big_int_minus_to_first(temp, n2);
        big_int_add_to_first(result, e);
    }
    big_int_free(temp);
    big_int_free(e);
    return result;
}

void big_int_div_to_first(big_int *n1, const big_int *n2){
    big_int *temp = big_int_div(n1, n2);
    big_int_assign(n1, temp);
    big_int_free(temp);
}

void big_int_mod_div(const big_int *n1, const big_int *n2){
    big_int *x = big_int_zero(); big_int_assign(x, n1);
    big_int *y = big_int_zero(); big_int_assign(x, n2);
    big_int *div = big_int_zero(); big_int *mod = big_int_zero();
    big_int *e = big_int_zero(); e->number[0] = 1;
    int k = 0;
    while (x->length != y->length){
        big_int_shift_add(y);
    }

}

big_int *big_int_mod_pow(big_int *x1, const big_int *y1, const big_int *m){
    big_int *y = big_int_zero(); big_int_assign(y, y1);
    big_int *x = big_int_zero(); big_int_assign(x, x1);
    big_int *two = big_int_zero(); two->number[0] = 2;
    big_int *result = big_int_zero(); result->number[0] = 1;
    big_int_mod_to_first(x, m);
    while (big_int_comp(y, big_int_zero())){
        if (y->number[0] % 2)
            big_int_multiply_to_first(result, x);
        big_int_multiply_to_first(x, x);
        big_int_mod_to_first(x, m);
        big_int_div_to_first(y, two);
    }
    big_int_free(y);
    big_int_free(x);
    big_int_free(two);
    return big_int_mod(result, m);
}

int main()
{
    big_int *m = big_int_get("111111111111111111111111111");
    big_int *h = big_int_get("11111111111");

    printf("m = "); big_int_print(m); big_int_print_0x(m);
    printf("h = "); big_int_print(h); big_int_print_0x(h);
    printf("--------------------------\n");

    // сумма
    big_int *sm = big_int_add(m, h);
    printf("sm = "); big_int_print(sm); big_int_print_0x(sm);
    printf("--------------------------\n");

    // разность
    big_int *r = big_int_minus(m, h);
    printf("привет = "); big_int_print(r); big_int_print_0x(r);
    big_int_print(big_int_minus(sm, m)); big_int_print_0x(big_int_minus(sm, m));
    printf("--------------------------\n");

    // умножение
    big_int *mlt = big_int_multiply(m, h);
    printf("mlt = "); big_int_print(mlt); big_int_print_0x(mlt);
    printf("--------------------------\n");

    // остаток от деления
    big_int *mod = big_int_mod(m, h);
    printf("mod = "); big_int_print(mod); big_int_print_0x(mod);
    printf("--------------------------\n");

    // остаток от деления
    big_int *div = big_int_div(m, h);
    printf("div = "); big_int_print(div); big_int_print_0x(div);
    printf("--------------------------\n");

    // сдвиг
    big_int_shift_minus(h);
    printf("h after shift = ");big_int_print(h); big_int_print_0x(h);
    printf("--------------------------\n");


    //mod_pow
    big_int *x = big_int_get("10111011");
    big_int *y = big_int_get("10111");
    big_int *m1 = big_int_get("10011");
    big_int *mod_pow = big_int_mod_pow(x, y, m1);
    printf("mod_pow= ");big_int_print(mod_pow); big_int_print_0x(mod_pow);
    printf("--------------------------\n");

    return 0;
}
