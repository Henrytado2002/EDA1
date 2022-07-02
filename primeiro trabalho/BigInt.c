#include "BigInt.h"
#include "DoubleLLists.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(BigInt a, BigInt b) {
    stnode current_a = Dfirst(a.num);
    stnode current_b = Dfirst(b.num);
    int control;

    if (a.num.size > b.num.size) {
        control = 1;
    } else if (b.num.size > a.num.size) {
        control = 2;
    } else {
        control = 3;
        while (current_a.next != NULL) {
            if (current_a.data > current_b.data) {
                control = 1;
                break;
            } else if (current_a.data < current_b.data) {
                control = 2;
                break;
            }
            current_a = *Advance(&current_a);
            current_b = *Advance(&current_b);
        }
    }
    return control;
}

BigInt big_new(char *num) {
    BigInt *NewBigInt = malloc(sizeof(Dlist));
    NewBigInt->num = CreateDList();
    int i;
    if (num[0] == '-') {
        NewBigInt->signal = 1;
        i = 1;
    } else {
        NewBigInt->signal = 0;
        i = 0;
    }
    while (i < strlen(num)) {
        char temp1[1];
        temp1[0] = num[i];
        int temp2 = atoi(temp1);
        insertlast(&NewBigInt->num, temp2);
        i++;
    }
    return *NewBigInt;
}

BigInt sum_b(BigInt a, BigInt b) {
    int pass = 0;
    BigInt res;
    res.num.size = 0;
    Dlist res_val = CreateDList();
    if (a.signal == b.signal) {
        //P+P
        if (a.signal == 0) {
            res.signal = 0;
            stnode current_a = Dlast(a.num);
            stnode current_b = Dlast(b.num);
            while (current_a.prev != NULL || current_b.prev != NULL) {
                insertfront(&res_val, (current_b.data + current_a.data + pass) % 10);
                if (current_a.data + current_b.data >= 10) {
                    pass = (current_a.data + current_b.data) / 10;
                } else {
                    pass = 0;
                }
                if (current_a.prev != NULL) {
                    current_a = *Back(&current_a);
                }
                if (current_b.prev != NULL) {
                    current_b = *Back(&current_b);
                }
            }
            if (pass != 0) {
                insertfront(&res_val, pass);
            }
            res.num = res_val;
            return res;
        }
        //N+N
        res.signal = 1;
        stnode current_a = Dlast(a.num);
        stnode current_b = Dlast(b.num);
        while (current_a.prev != NULL || current_b.prev != NULL) {
            insertfront(&res_val, (current_b.data + current_a.data + pass) % 10);
            if (current_a.data + current_b.data >= 10) {
                pass = (current_a.data + current_b.data) / 10;
            } else {
                pass = 0;
            }
            if (current_a.prev != NULL) {
                current_a = *Back(&current_a);
            }
            if (current_b.prev != NULL) {
                current_b = *Back(&current_b);
            }
        }
        if (pass != 0) {
            insertfront(&res_val, pass);
        }
        res.num = res_val;
        return res;
    }
    //P+N
    if (a.signal == 0) {
        b.signal = 0;
        return sub_b(a, b);
    }
    //N+P
    a.signal = 0;
    return sub_b(b, a);
}

BigInt sub_b(BigInt a, BigInt b) {
    BigInt res;
    int pass = 0;
    int control; //1->O primeiro é maior || 2->O segundo é maior || 3->São iguais
    Dlist res_num = CreateDList();
    stnode current_a = Dfirst(a.num);
    stnode current_b = Dfirst(b.num);

    if (a.signal == b.signal) {
        //ver qual dos números é maior
        if (a.num.size > b.num.size) {
            res.signal = 0;
            control = 1;
        } else if (b.num.size > a.num.size) {
            res.signal = 1;
            control = 2;
        } else {
            control = 3;
            while (current_a.next != NULL) {
                if (current_a.data > current_b.data) {
                    control = 1;
                    break;
                } else if (current_a.data < current_b.data) {
                    control = 2;
                    break;
                }
                current_a = *Advance(&current_a);
                current_b = *Advance(&current_b);
            }
        }
        //se forem iguais
        if (control == 3) {
            res.signal = 0;
            insertfront(&res_num, 0);
            res.num = res_num;
            return res;
        }
        current_a = Dlast(a.num);
        current_b = Dlast(b.num);
        //P-P
        if (a.signal == 0) {
            if (control == 1) {
                res.signal = 0;
                while (current_a.prev != NULL || current_b.prev != NULL) {
                    current_a.data -= pass;
                    if (current_a.data < current_b.data) {
                        current_a.data += 10;
                        pass = 1;
                        insertfront(&res_num, current_a.data - current_b.data);
                    } else {
                        pass = 0;
                        insertfront(&res_num, current_a.data - current_b.data);
                    }
                    if (current_a.prev != NULL) {
                        current_a = *Back(&current_a);
                    }
                    if (current_b.prev != NULL) {
                        current_b = *Back(&current_b);
                    }
                }
                res.num = res_num;
                return res;
            } else {
                res.signal = 1;
                while (current_a.prev != NULL || current_b.prev != NULL) {
                    current_b.data -= pass;
                    if (current_b.data < current_a.data) {
                        current_b.data += 10;
                        pass = 1;
                        insertfront(&res_num, current_b.data - current_a.data);
                    } else {
                        pass = 0;
                        insertfront(&res_num, current_b.data - current_a.data);
                    }
                    if (current_a.prev != NULL) {
                        current_a = *Back(&current_a);
                    }
                    if (current_b.prev != NULL) {
                        current_b = *Back(&current_b);
                    }
                }
                res.num = res_num;
                return res;
            }
        }
        //N-N
        if (a.signal == 1) {
            if (control == 1) {
                res.signal = 1;
                while (current_a.prev != NULL || current_b.prev != NULL) {
                    current_a.data -= pass;
                    if (current_a.data < current_b.data) {
                        current_a.data += 10;
                        pass = 1;
                        insertfront(&res_num, current_a.data - current_b.data);
                    } else {
                        pass = 0;
                        insertfront(&res_num, current_a.data - current_b.data);
                    }
                    if (current_a.prev != NULL) {
                        current_a = *Back(&current_a);
                    }
                    if (current_b.prev != NULL) {
                        current_b = *Back(&current_b);
                    }
                }
                res.num = res_num;
                return res;
            } else {
                res.signal = 0;
                while (current_a.prev != NULL || current_b.prev != NULL) {
                    current_b.data -= pass;
                    if (current_b.data < current_a.data) {
                        current_b.data += 10;
                        pass = 1;
                        insertfront(&res_num, current_b.data - current_a.data);
                    } else {
                        pass = 0;
                        insertfront(&res_num, current_b.data - current_a.data);
                    }
                    if (current_a.prev != NULL) {
                        current_a = *Back(&current_a);
                    }
                    if (current_b.prev != NULL) {
                        current_b = *Back(&current_b);
                    }
                }
                res.num = res_num;
                return res;
            }
        }
    }
    //P-N
    if (a.signal == 0) {
        b.signal = 0;
        return sum_b(a, b);
    }
    //N-P
    b.signal = 1;
    return sum_b(a, b);
}

BigInt mult_b(BigInt a, BigInt b) {
    stnode current_a = Dlast(a.num);
    stnode current_b = Dlast(b.num);
    BigInt res_temp1;
    BigInt res_temp2;
    res_temp1.signal = 0;
    res_temp2.signal = 0;
    BigInt res;
    Dlist res_num = CreateDList();
    int pass = 0;
    int i;
    int j;
    int k = 0;
    Dlist stack[b.num.size];

    //casos base (zeros)---------------------
    if (a.num.size == 1 && a.num.head->next->data == 0 || b.num.size == 1 && b.num.head->next->data == 0) {
        res.signal = 0;
        insertfront(&res_num, 0);
        res.num = res_num;
        return res;
    }

    //inicializar a stack das listas que vão conter os números para a adição
    for (i = 0; i < b.num.size; i++) {
        stack[i] = CreateDList();
    }

    //PxP || NxN
    if (a.signal == b.signal) {
        res.signal = 0;
    }
    //PxN || NxP
    if (a.signal != b.signal) {
        res.signal = 1;
    }
    for (i = 0; i < b.num.size; i++) {
        //parte da multiplicação
        while (k < i) {
            insertfront(&stack[i], 0);
            k++;
        }
        k = 0;
        for (j = 0; j < a.num.size; j++) {
            if (current_a.data * current_b.data + pass >= 10) {
                insertfront(&stack[i], (current_a.data * current_b.data + pass) % 10);
                pass = (current_a.data * current_b.data + pass) / 10;
            } else {
                insertfront(&stack[i], current_a.data * current_b.data + pass);
                pass = 0;
            }
            current_a = *Back(&current_a);
            if (j + 1 == a.num.size && pass != 0) {
                insertfront(&stack[i], pass);
            }
        }
        current_a = Dlast(a.num);
        current_b = *Back(&current_b);
    }
    //parte da adição
    res_temp1.num = stack[0];
    for (i = 1; i < b.num.size; i++) {
        res_temp2.num = stack[i];
        res_temp1 = sum_b(res_temp2, res_temp1);
    }
    res.num = res_temp1.num;
    return res;
}

BigInt div_b(BigInt a, BigInt b) {
    BigInt res = big_new("0");
    BigInt unit = big_new("1");
    int control;
    //verificar qual é maior
    control = compare(a,b);
    // N/0
    if (b.num.size == 1 && b.num.head->next->data == 0) {
        printf("impossivel dividir por zero\n");
        res.signal = 0;
        return res;
    }
    // O/N || A<B
    if (a.num.size == 1 && a.num.head->next->data == 0 || control == 2) {
        res.signal = 0;
        return res;
    }
    // N/N
    if (control == 3) {
        res.signal = 0;
        res = sum_b(res, unit);
        return res;
    }
    // A>B
    if (a.signal == b.signal) {
        res.signal = 0;
    } else {
        res.signal = 1;
    }
    BigInt temp = b;
    control = 1;
    while (control == 1) {
        temp = sum_b(temp, b);
        control = compare(a,temp);
        res = sum_b(res, unit);
    }
    if(compare(a,temp)==3){
        res= sum_b(res, unit);
    }
    return res;
}

BigInt mod_b(BigInt a, BigInt b) {
    BigInt res = big_new("0");
    BigInt unit = big_new("1");
    int control;
    res.signal=0;
    control = compare(a,b);
    // N/0
    if (b.num.size == 1 && b.num.head->next->data == 0) {
        printf("impossivel dividir por zero\n");
        return res;
    }
    // O/N || A<B
    if (a.num.size == 1 && a.num.head->next->data == 0 || control == 2) {
        return res;
    }
    // N/N
    if (control == 3) {
        res = sum_b(res, unit);
        return res;
    }
    // A>B
    BigInt module;
    module= sub_b(a, mult_b(b, div_b(a,b)));
    return module;
}

void print_b(BigInt a) {
    if (a.signal == 1) {
        printf("-");
    }
    stnode *current = a.num.head->next;
    while (current != a.num.tail) {
        printf("%d", current->data);
        current = Advance(current);
    }
    printf("\n");
}
