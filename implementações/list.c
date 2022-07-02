#include "list.h"
#include <stdlib.h>
#include "fatal.h"
#include <stdbool.h>


struct Node{
    ElementType Element;
    Position    Next;
};


List CreateList()
{
    List L;
    L = malloc( sizeof( struct Node ) );
    if( L == NULL ){ 
        FatalError( "Out of memory!" );
    }
    L->Next = NULL;
    return L;
}

void MakeEmpty( List L ){
DeleteList(L);
}


bool IsEmpty( List L ){
    if(L->Next==NULL){ 
        return true;
    }
    return false;
}

bool IsLast( Position P, List L ){
    if(L->Next==NULL){
        return true;
    }
    return false;
}

Position Find( ElementType X, List L ){
}


Position FindPrevious( ElementType X, List L ) {
    return NULL;
}


void Insert( ElementType X, List L, Position P ) {

}

void Delete( ElementType X, List L ){
}


void DeleteList( List L ) {
    
}


Position Header( List L ) {
    return NULL;
}


Position First( List L ) {
    return NULL;
}


Position Advance( Position P ) {
    P=P->Next;
    return P;
}


ElementType Retrieve( Position P ) {
    return P->Element;
}

void PrintList(List L){
    printf("( ");
    Position P=L->Next;
    while(P!=NULL){
        printf("%d ",P->Element);
        P=Advance(P);
    }
    printf(" )\n");
}

int main(){
    List L = CreateList();
    if(IsEmpty(L)){
        printf("esta vazia\n");
    }
    PrintList(L);
}