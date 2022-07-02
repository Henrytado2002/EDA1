#include "stackar.h"
#include "fatal.h"
#include <stdlib.h>


#define EmptyTOS ( -1 )
#define MinStackSize ( 5 )


struct StackRecord
{
    int Capacity;
    int TopOfStack;
    ElementType *Array;
};



Stack CreateStack( int MaxElements )
{

    Stack S;	

	if( MaxElements < MinStackSize )
		Error( "Stack size is too small" );

	S = malloc( sizeof( struct StackRecord ) );
	if( S == NULL )
		FatalError( "Out of space!!!" );

	S->Array = malloc( sizeof( ElementType ) * MaxElements );
	if( S->Array == NULL )
		FatalError( "Out of space!!!" );

	S->Capacity = MaxElements;
	MakeEmpty( S );

	return S;
}



void DisposeStack( Stack S )
{
    if( S != NULL )
    {
        free( S->Array );
        free( S );
    }
}


int IsEmpty( Stack S )
{
   return S->TopOfStack==-1; 
}


int IsFull( Stack S )
{
    return S->TopOfStack==S->Capacity-1;

}


void MakeEmpty( Stack S )
{
    S->TopOfStack=-1;
}


void Push( ElementType X, Stack S )
{
    if(!IsFull(S)){ 
        S->TopOfStack++;
        S->Array[S->TopOfStack]=X;
        printf("%d successfully pushed.\n", X);
    }
    else{
        printf("stack is full.\n");
    }
}


ElementType Top( Stack S )
{
    return S->Array[S->TopOfStack];
}


ElementType Pop( Stack S )
{
    if(!IsEmpty(S)){ 
        ElementType top = S->Array[S->TopOfStack];
        S->TopOfStack--;
        printf("%d successfully popped.\n", top);
        return top;
    }
    else{
        printf("Stack is empty.\n");   
    }
}

int main(){
    return 0;
}