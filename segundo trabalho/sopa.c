#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "hash_tables.c"
#include <string.h>

#define max_y 16
#define max_x 20


struct puzzle{
    hashtbl lista;
    hashtbl lista_prefixos;
    char sopa[max_y][max_x];
    int dim_x;
    int dim_y;
}typedef puzzle;

struct solucao{
    int num;
    char last_found[64];
    hashtbl encontradas;
}typedef solucao;
//numero de characteres que compoem o numero de palavras guardadas do ficheiro ()
#define size_num 3

//insere as palavras que estão no ficheiro de nome "name"
//começa por ler o numero de palavras no ficheiro
void word_store(char*name, puzzle* puzzle){
    FILE* fp;
    fp = fopen("puzzle.txt", "r");
    char* size_char = malloc(size_num*sizeof(char));
    fgets(size_char, 3, fp);
    size_char[size_num-1]= '\0';
    int  size = strtol(size_char, NULL, 10);
    //createtable(size*2);
    char word[64];
    char prefix[64];
    hashtbl table_words = createtable(nextprime(size));
    hashtbl* tbl_pt = &table_words;
    hashtbl table_prefixes = createtable(nextprime(size*8));
    hashtbl* tbl_pr_pt = &table_prefixes;

    //esta linha de código serve exclusivamente para corrigir um problema que acontecia aquando da leitura da primeira palavra
    //a primeira palavra do ficheiro retornava como um espaço em branco
    fgets(word, 64, fp);

    //inserção das palavras a procurar
    int i=0;
    while(size>0){
        fgets(word, 64, fp);    
        word[strlen(word)-2]='\0'; 
        while(word[i]!='\0'){
            prefix[i]=word[i];
            if(find(prefix, table_prefixes)==-1){
                insert(tbl_pr_pt,prefix);
            }
            i++;
        }
        insert(tbl_pt,word);
        size--;
        i=0;
        memset(prefix, 0, 64);
    }
    puzzle->lista=table_words;
    puzzle->lista_prefixos=table_prefixes;

    //leitura e conversão das dimensões do array
    i = 0;
    int j = 0;
    int dimx, dimy;
    char word2[64];
    fgets(word, 64, fp);
    i = strcspn(word, " ")+1;
    while(word[i]!= '\n'){ 
        word2[j]=word[i];
        i++;
        j++;
    }
    dimy = atoi(word);
    dimx = atoi(word2);
    puzzle->dim_y=dimy;
    puzzle->dim_x=dimx;

    //transição dos caracteres no ficheiro para as posições respectivas no array da sopa de letras
    i=0;
    j=0;
    int seq = 0;
    do{
        fgets(word, 64, fp);
        while(!(word[seq]=='\n' || word[seq]=='\0')){
            if(word[seq]!=' '){
                puzzle->sopa[i][j] = word[seq];
                j++;
            }
            seq++;
        }
        seq=0;
        j=0;
        i++;
    }while(i<dimy);
}


void print_sopa(puzzle puzzle){
    int i,j;
    printf("sopa:\n");
    for(i=0 ; i<puzzle.dim_y ; i++){
        for(j=0 ; j<puzzle.dim_x ; j++){
            printf("%c ", puzzle.sopa[i][j]);
            
        }
        j=0;
        printf("\n");
    }
}   

//verifica, para a direção especificada, se existe alguma palavra presente na tabela de palavras 
//se encontrar retorna 1, se não retorna 0
int direction(puzzle puzz, int i, int j, int add_i, int add_j, solucao*ret){
    int count=0;
    char word[64];
    // 0<=i+add_i<dimy
    // 0<=j+add_j<dimx

    hashtbl* update = &ret->encontradas;
    
    while(i>=0 && i<puzz.dim_y && j>=0 && j<puzz.dim_x){
        word[count]=puzz.sopa[i][j];

        //se não estiver presente nos prefixos, não vale a pena continuar a procurar
        if(find(word, puzz.lista_prefixos)==-1){
            return 0;
        }

        //caso a string esteja presente na lista, retorna-a e dá update á solução
        if(find(word, puzz.lista)!=-1){
            insert(update,word);
            strcpy(ret->last_found, word);
            ret->num++;
            return 1;
        }
    }

    //se chegar ao fim das dimensões e não encontrar:
    return 0;
}

//procura, na sopa de letras, as palavras presentes na lista
solucao seek(puzzle puzzle){
    int i;
    int j;
    int direc_ret;
    char direc[3];
    solucao ret;
    ret.encontradas = createtable(23);
    ret.num=0;
    solucao* ret_ptr = &ret;
    for(i=0; i<puzzle.dim_y; i++){
        for(j=0; i<puzzle.dim_x; j++){
            
            //north
            strcpy(direc, "N");
            direc_ret=direction(puzzle, i, j, -1, 0, ret_ptr);
            if(direc_ret == 1){
                printf("encontrada %s na direção %s, posição %dx%d.\n",ret.last_found, direc, i, j );
            }
            
            //south
            strcpy(direc, "S");
            direc_ret=direction(puzzle, i, j, 1, 0, ret_ptr);
            if(direc_ret == 1){
                printf("encontrada %s na direção %s, posição %dx%d.\n",ret.last_found, direc, i, j );
            }
            
            //east
            strcpy(direc, "E");
            direc_ret=direction(puzzle, i, j, 0, 1, ret_ptr);
            if(direc_ret == 1){
                printf("encontrada %s na direção %s, posição %dx%d.\n",ret.last_found, direc, i, j );
            }
            
            //west
            strcpy(direc, "W");
            direc_ret=direction(puzzle, i, j, 1, -1, ret_ptr);
            if(direc_ret == 1){
                printf("encontrada %s na direção %s, posição %dx%d.\n",ret.last_found, direc, i, j );
            }

            
            //north-east
            strcpy(direc, "NE");
            direc_ret=direction(puzzle, i, j, -1, 1, ret_ptr);
            if(direc_ret == 1){
                printf("encontrada %s na direção %s, posição %dx%d.\n",ret.last_found, direc, i, j );
            }

            
            //north- west
            strcpy(direc, "NW");
            direc_ret=direction(puzzle, i, j, -1, -1, ret_ptr);
            if(direc_ret == 1){
                printf("encontrada %s na direção %s, posição %dx%d.\n",ret.last_found, direc, i, j );
            }

            
            //south-east
            strcpy(direc, "SE");
            direc_ret=direction(puzzle, i, j, 1, 1, ret_ptr);
            if(direc_ret == 1){
                printf("encontrada %s na direção %s, posição %dx%d.\n",ret.last_found, direc, i, j );
            }

            
            //south-west
            strcpy(direc, "SW");
            direc_ret=direction(puzzle, i, j, 1, -1, ret_ptr);
            if(direc_ret == 1){
                printf("encontrada %s na direção %s, posição %dx%d.\n",ret.last_found, direc, i, j );
            }
        }
    }
    return ret;
}

int main(){
    puzzle sopa_letras;
    puzzle* sopa_letras_ptr;
    sopa_letras_ptr= &sopa_letras;

    word_store("puzzle.txt", sopa_letras_ptr);
 //   printf("lista de palavras:\n");
 //   printtable(sopa_letras.lista);
 //   printf("lista de prefixos:\n");
 //   printtable(sopa_letras.lista_prefixos);
 //   print_sopa(sopa_letras);
    printf("lista de palavras:\n");
    printtable(sopa_letras.lista);
    printf("\nlista de prefixos:\n");
    printtable(sopa_letras.lista_prefixos);
    printf("resultado do find:%d\n", find("pomar", sopa_letras.lista_prefixos));
    print_sopa(sopa_letras);
}