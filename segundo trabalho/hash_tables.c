#include <stdio.h>
#include <stdlib.h>
#include <string.h>


hashtbl createtable(int size) {
    hashtbl hashtable;
    hashtable.table = malloc(size * sizeof(node));
    hashtable.filled = malloc(sizeof(int));
    for (int i = 0; i < size; i++) {
        hashtable.table[i].key = i;
        strcpy(hashtable.table[i].word, ".");
        hashtable.table[i].word[0] = '.';
    }
    hashtable.size = size;

    *hashtable.filled = 0;
    return hashtable;
}

void destroytable(hashtbl *h) {
    free(h);
}

//caso encontre a palavra, retorna a key, caso não retorna -1
int find(char* word, hashtbl h) {
    int i = 0;
    int sum = 0;

    while (word[i] != '\0') {
        sum += word[i];
        i++;
    }
    int key = sum % h.size;
    
    while(strcmp(word, h.table[key].word)!=0){ 
        if(h.table[key].word[0]=='.'){
            return -1;   //caso não encontre a palavra, retorna -1
        }
        //acesso quadratico
        int k = 1;
        int key2 = key;
        while (h.table[key2].word[0] != '.' && strcmp(word, h.table[key2].word)!=0) {
            key2 = (key + (k * k)) % h.size;
            k++;
        }
        key = key2;
    }
    return key;
}

//vai procurar o próximo segundo número primo a partir de um número dado com argumento
//usa-se o segundo e não o imediatamente próximo para que não haja problemas de rehashing duas vezes seguidas
int nextprime(int prev) {
    int i = prev + 1;
    int k = 2;
    int count =0;
    while (1) {
        while (i % k != 0 && k < i) {
            k++;
        }
        if (i == k) {
            count++;
        }
        if(count == 1){
            break;
        }
        k = 2;
        i++;
    }
    return i;
}

void insert(hashtbl *h, char *word) {
    hashtbl table=*h;
    if (loadfactor(table) > 0.6) {
        rehash(h);
    }
    table=*h;
    //hash function that will generate the key where to insert
    //the sum of the ascii characters devided by the size of the table
    //key will be the leftover
    int i = 0;
    int sum = 0;
    while (word[i] != '\0') {
        sum += word[i];
        i++;
    }
    int key = sum % table.size;

    //collision management
    //quadratic access
    int k = 1;
    int key2 = key;
    while (table.table[key2].word[0] != '.') {
        key2 = (key + (k * k)) % table.size;
        k++;
    }
    key = key2;
    strcpy(table.table[key].word, word);
    table.filled=table.filled+1;
    *h=table;
}

void rehash(hashtbl *h) {
    int newsize;
    hashtbl oldtable = *h;
    newsize = nextprime(oldtable.size);
    hashtbl newtable = createtable(newsize);
    *h=newtable;
    int i = 0;
    while (i < oldtable.size) {
        if(oldtable.table[i].word[0]!='.') {
            insert(h, oldtable.table[i].word);

        }
        i++;
    }
    newtable.filled = oldtable.filled;
    *h=newtable;
}

// λ = N/M
// N = nº de chaves inseridas
// M = tamanho do vector (deve ser primo)
float loadfactor(hashtbl h) {
    float filled = *h.filled;
    float size= h.size;
    float ret;
    ret = filled / size;
    return ret;
}

void printtable(hashtbl h){
    printf("\nkey | word | size: %d\n---------------------------------\n",h.size);
                            
    for(int i=0; i<h.size; i++){
        if(h.table[i].key<10) {
            printf("   %d | %s \n", h.table[i].key, h.table[i].word);
        }
        else if(h.table[i].key<100){
            printf("  %d | %s \n", h.table[i].key, h.table[i].word);
        }
        else {
            printf(" %d | %s \n", h.table[i].key, h.table[i].word);
        }
    }
    printf("----------------------------------\n");
}

char* retrieve(int key, hashtbl h){
    return h.table[key].word;
}
