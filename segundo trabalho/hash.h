
#include <stdbool.h>

typedef unsigned int Index;
typedef Index Position;


struct hashtable {
    char word[32];
    int key;
} typedef node;

struct hashtable2 {
    node *table;
    int *filled;
    int size;
} typedef hashtbl;

//esta função compara duas strings (1=iguais, 0=diferentes)
int compare(char* str1, char* str2);

//cria uma nova tabela de acordo com as especificações 
hashtbl createtable(int size);                  //feito e testado

//dá free á memória ocupada pela tabela
void destroytable(hashtbl *h);                   //feito

//dada uma palavra, vai retornar a key de onde essa palavra está na tabela se a encontrar
//caso não encontre a palavra, retorna -1 
int find(char* word, hashtbl h);                   //feito

//dada uma word, pela função de hash do código, vai inserir a palavra na tabela
void insert(hashtbl *h, char *word);            //feito

//dada uma key, retorna a palavra guardada nessa key
char* retrieve(int key, hashtbl h);

//cria uma nova tabela de tamanho igual ao  terceiro número primo depois do tamanho da tabela antiga
//copia tudo o que estava na tabela antiga para a tabela nova e retorna-a
void rehash(hashtbl *h);                      //feito

//mostra a tabela no trminal
void printtable(hashtbl h);                     //feito e testeado

//de acordo com a expressão , retorna o fator de carga da tabela
float loadfactor(hashtbl h);                    //feito

//a partir de um número primo, vai contar três primos e retornar o terceiro
//retorna-se o terceiro primo como failsafe para rehashing duas vezes seguidas 
int nextprime(int prev);                        //feito