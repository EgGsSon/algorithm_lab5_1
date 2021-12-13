
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
typedef struct Cell {
    char key[21];
    char value[21];
} cell;
 
int power(int a, int b) {
    int value = 1;
    for(int i = 0; i < b; i++)
        value *= a;
    return value;
}

unsigned int Hash(char key[21], int div, int range) {
    int i = 0;
    unsigned int res = 0;
    
    while(key[i] != '\0') {
        res += (key[i] - 'a') * power(div, i);
        i++;
    }
    
    return (res % range);
}

cell *Search(int div, int range, cell table[range], char key[21]) {
    int hash = Hash(key, div, range);
    if(strcmp(table[hash].key, key) == 0)
        return &table[hash];
    return NULL;
}

void Insert(int range, int div, cell table[range], char key[21], char value[21]) {
    unsigned int hash = Hash(key, div, range);
    strcpy(table[hash].key, key);
    strcpy(table[hash].value, value);
}

void Delete(int div, int range, cell table[range], char key[21]) {
    cell *node = Search(div, range, table, key);
    if(node != NULL) {
        memset(node->key, 0, 21);
        memset(node->value, 0, 21);
    }
}
 
int main(int argc, const char * argv[]) {
    FILE *file = fopen("map.in","r");
    FILE *fileout = fopen("map.out","w");
     
    int div = 29;
    int range = 100001;
    char word[21];
    char key[21];
    char oper[8];
    cell table[range];
     
    fscanf(file, "%s", oper);
    fscanf(file, "%s", key);
     
    while(feof(file) == 0) {
        if(strcmp(oper, "put") == 0) {
            fscanf(file, "%s", word);
            Insert(range, div, table, key, word);
        }
        
        if(strcmp(oper, "get") == 0) {
            cell *node = Search(div, range, table, key);
            if(node != NULL)
                fprintf(fileout, "%s\n", node->value);
            else
                fprintf(fileout, "none\n");
        }
         
        if(strcmp(oper, "delete") == 0) {
            Delete(div, range, table, key);
        }
         
        fscanf(file, "%s", oper);
        fscanf(file, "%s", key);
    }
    
    fclose(fileout);
    fclose(file);
    
    return 0;
}
