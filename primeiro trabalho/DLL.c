#include "DoubleLLists.h"
#include <stdio.h>
#include <stdlib.h>


Dlist CreateDList() {
    stnode *h = malloc(sizeof(Dlist));
    stnode *t = malloc(sizeof(Dlist));
    if (h == NULL || t == NULL) {
        printf("out of memory\n");
        exit(1);
    }
    t->next = NULL;
    t->prev = h;
    h->prev = NULL;
    h->next = t;
    Dlist L;
    L.head = h;
    L.tail = t;
    L.size = 0;
    L.head->data=0;
    L.tail->data=0; // este valor vai ajudar nas operações dos BigInts
    return L;
}

void insertfront(Dlist *L, int num) { //insere no inicio da lista
    stnode *newnode = malloc(sizeof(stnode));
    newnode->data = num;
    newnode->next = L->head->next;
    newnode->prev = L->head;
    L->head->next->prev = newnode;
    L->head->next = newnode;
    L->size++;
}

void insertlast(Dlist *L, int num) { //insere no fim da lista
    stnode *newnode = malloc(sizeof(stnode));
    newnode->data = num;
    newnode->prev = L->tail->prev;
    newnode->next = L->tail;
    L->tail->prev->next = newnode;
    L->tail->prev = newnode;
    L->size++;
}

int SizeDList(Dlist L) {
    return L.size;
}

stnode Dfirst(Dlist L) {
    return *L.head->next;
}

stnode Dlast(Dlist L) {
    return *L.tail->prev;
}

int IsEmptyDList(Dlist L) {
    if (L.head->next == L.tail) {
        return 1;
    }
    return 0;
}

stnode *Advance(stnode *P) {
    return P->next;
}

stnode *Back(stnode *P) {
    return P->prev;
}

void MakeEmptyDList(Dlist L) {
    if (IsEmptyDList(L)) {
        printf("a lista já está vazia \n");
        exit(1);
    }
    stnode *current = L.head;
    while (current != L.tail) {
        stnode *temp = current;
        current = Advance(current);
        free(temp);
    }
}

//retorna a posição em memória do nó da primeira instância do elemento "e" dado no argumento
stnode *FindinDList(ElementType e, Dlist L) {
    if (IsEmptyDList(L)) {
        printf("a lista está vazia \n");
        exit(1);
    }
    stnode *current = L.head->next;
    while (current != L.tail->prev) {
        if (current->data == e) {
            return current;
        }
        current = Advance(current);
    }
    printf("O elemento referido não foi encontrado na lista.\n");
}

//elimina a primeira instância do elemento "e" da lista.
void DeleteElement(ElementType e, Dlist L) {
    if (IsEmptyDList(L)) {
        printf("a lista está vazia \n");
        exit(1);
    }
    stnode *current = L.head->next;
    while (current != L.tail->prev) {
        if (current->data == e) {
            current->prev->next = current->next;
            current->next->prev = current->prev;
            free(current);
            return;
        }
        current = Advance(current);
    }
    printf("O elemento referido não foi encontrado na lista.\n");
}

ElementType nodedata(stnode P) {
    return P.data;
}

void insertatposition(int P, Dlist *L) {
    int i = 1;
    stnode *current = L->head->next;
    while (i != P) {
        current = Advance(current);
        i++;
    }
    stnode newnode;
    current->prev->next = &newnode;
    newnode.prev = current->prev;
    current->prev = &newnode;
    newnode.next = current;
    L->size++;
}

ElementType Removeatposition(int P, Dlist *L) {
    int i = 1;
    stnode *current = L->head->next;
    while (i != P) {
        current = Advance(current);
        i++;
    }
    int data = current->data;
    current->prev->next = current->next;
    current->next->prev = current->prev;
    free(current);
    L->size--;
    return data;
}

void PrintDList(Dlist L) {
    stnode *current = L.head->next;
    while (current != L.tail) {
        printf("%d", current->data);
        current = Advance(current);
        if (current != L.tail) {
            printf(" - ");
        }
    }
    printf("\n");
}




