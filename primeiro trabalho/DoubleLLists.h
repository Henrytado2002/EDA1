
#ifndef doubleLList_h
#define doubleLList_h

#include <stdio.h>

typedef int ElementType;

typedef struct node {
    int data;
    struct node *next;
    struct node *prev;
} stnode;

typedef struct Dlist {
    int size;
    struct node *head;
    struct node *tail;
} Dlist;

Dlist CreateDList();                        //
void MakeEmptyDList(Dlist L);                  //
int SizeDList(Dlist L);                         //
stnode Dfirst(Dlist L);                         //
stnode Dlast(Dlist L);                          //
int IsEmptyDList(Dlist L);                      //
void insertlast(Dlist *L, int num);            //
void insertfront(Dlist *L, int num);            //
stnode *FindinDList(ElementType e, Dlist L);    //
void insertatposition(int P, Dlist *L);          //
void DeleteElement(ElementType e, Dlist L);     //
ElementType Removeatposition(int P, Dlist *L);   //
stnode *Advance(stnode *P);             //
stnode *Back(stnode *P);                //
ElementType nodedata(stnode P);         //
void PrintDList(Dlist L);               //
#endif /* doubleLList_h */