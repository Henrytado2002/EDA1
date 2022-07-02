//
//  Complete o programa para que seja possível, ler uma
//  expressão em infix e fazer a conversão para postfix
//  usando o algoritmo dexcrito nas aulas teóricas
//
//
//  Created by Ligia Ferreira on 12/03/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fatal.h"
#include <ctype.h>
#include "stackar.h"



#define EmptyTOS ( -1 )
#define MinStackSize ( 5 )


struct StackRecord
{
    int Capacity;
    int TopOfStack;
    ElementType *Array;
};


// função que cria um array na stack e retorna o seu endereço
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

    return S->TopOfStack == -1;
}


int IsFull( Stack S )
{
    if (S->TopOfStack == S->Capacity-1) 
    {
        return 1;
    }
    else
    {
        return 0;
    }
}



void MakeEmpty( Stack S )
{
    S -> TopOfStack = -1;
}


void push( ElementType X, Stack S )
{
    if (IsFull(S))
    {
        Error("A stack está cheia"); 
    }
    else{
        S -> TopOfStack++;
        S ->Array[S-> TopOfStack]=X;
    }
}


ElementType top( Stack S )
{
    if (!IsEmpty(S))
    {
        return S->Array[S->TopOfStack];
    }
    Error("Stack is empty");
}

void balance(char array[50], int sz){
	int i=0;
	int count1=0;
	int count2=0;
	while(array[i]!='\0'){
		if(array[i]=='('){
			count1++;
		}
		else if(array[i]==')'){
			count2++;
		}
		i++;
	}
	if(count1==count2){printf("tá balanciadu");}
	else{printf("tá desbalanciadu");}
}


ElementType pop( Stack S )
{
    int cenas;
    if (!IsEmpty(S))
    {
        cenas = S->Array[S->TopOfStack];
        S->TopOfStack--;
        return cenas;
    }
    Error("Stack is empty");
}



int priority(char c){
   
    return 1;
}


char *ler_input(){
    static char name[100];
    printf("Os tokens devem aprearecer separados por espaço \n");
    
    printf("Exemplo ( 2 + 6 ) * 10 \n");
    printf("infix : ");
    scanf("%s[^\n]s",name);
    return name;
}


int isNumber(char *token){
    if(isdigit(token[0]) || token[0]=='-' && isdigit(token[1])){
        return 1;
    }
    return 0;
}

char *tostring(char x){
    static char toReturn[2];
    toReturn[0]=x;
    toReturn[1]='\0';
    return toReturn;
}

// usar strtok para tokenizar a string input
// usar strcat pata concatenar strings

void conversion(char input[], char output[], Stack s){
    
    char* token;
    output[0]='\0';
    token=strtok(input," ");
    while (token !=NULL){
        printf("token %s\n",token);
        printf("%d\n",isNumber(token));
        if(isNumber(token)){push(token, s);}
        token=strtok(NULL," ");
    }


}

int main(int argc, const char * argv[]) {
  
    char* infix;
    infix=ler_input();
    Stack s = CreateStack(strlen(infix));
    char postfix[strlen(infix)];
    conversion(infix, postfix, s);
    printf("postfix-> %s\n",postfix);
    
    return 0;
}