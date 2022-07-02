#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"
#include "fatal.h"


#define MinQueueSize ( 5 )

struct QueueRecord{
    int Capacity;
    int Front;
    int Rear;
    ElementType *Array;
};


/* FUNCOES AUXILIARES */
/* numero de elementos na fila */
int size( Queue Q ){
    return Q->Capacity-1;
}


/* indice do proximo elemento  */
int successor( int i, Queue Q ){
    if(i+1 > Q->Capacity-1){
        return 0;
    }
    return i+1;
}



/* FUNCOES DE MANIPULACAO DE QUEUES */
Queue CreateQueue( int MaxElements ){
    Queue Q;

    if( MaxElements < MinQueueSize )
        Error( "Queue size is too small" );

    Q = malloc( sizeof( struct QueueRecord ) );
    if( Q == NULL )
        FatalError( "Out of space!!!" );

    Q->Array = malloc( sizeof( ElementType ) * MaxElements );
    if( Q->Array == NULL )
        FatalError( "Out of space!!!" );

    Q->Capacity = MaxElements+1;
    MakeEmptyQueue( Q );

    return Q;
}


void DisposeQueue( Queue Q ){
    if( Q != NULL ){
        free( Q->Array );
        free( Q );
    }
}


bool IsEmptyQueue( Queue Q ){
    return Q->Front==Q->Rear;
}


bool IsFullQueue( Queue Q ){
    if(Q->Front==0){
        return size(Q)-1;
    }
    else if(Q->Front==1){
        return size(Q);
    }
    return Q->Rear=Q->Front-2;
}


void MakeEmptyQueue( Queue Q ){
   Q->Rear=Q->Front;
}


void Enqueue( ElementType X, Queue Q ){
    if(!IsFullQueue(Q)){
        Q->Array[Q->Rear]=X;
        Q->Rear=successor(Q->Rear, Q);
    }
}


ElementType Front( Queue Q ){
    return Q->Array[Q->Front];
}


ElementType Dequeue( Queue Q ){
    ElementType A;
    if(!IsEmptyQueue(Q)){
        A=Q->Array[Q->Rear];
        if(!(Q->Rear-1<0)){
            Q->Rear--;
        }
        else{
            Q->Rear=size(Q);
        }
    }
}

int main(){
    
}