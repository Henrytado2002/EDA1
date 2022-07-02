#include "BigInt.h"
#include "DoubleLLists.h"
#include <stdio.h>

int main() {

    //sejam a = 1000000 e b = 90000
    BigInt a = big_new("20");
    BigInt b =  big_new("15");
    BigInt res;

    //adição
    res = sum_b(a, b);
    printf("a + b = ");
    print_b(res);
    printf("\n");

    //subtração
    res = sub_b(a,b);
    printf("a - b = ");
    print_b(res);
    printf("\n");

    //multiplicação
    res = mult_b(a,b);
    printf("a * b = ");
    print_b(res);
    printf("\n");

    //divisão
    res = div_b(a,b);
    printf("a / b = ");
    print_b(res);
    printf("\n");

}