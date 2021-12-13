
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
typedef struct Cell {
    struct Cell *next;
    struct Cell *prev;
    int value;
} cell;
 
unsigned int Hash(int value, int div) {
    return abs(value % div);
}
 
cell *Search(int div, cell table[div], int value) {
    cell *node = table[Hash(value, div)].next;
    while(node != NULL && node->value != value)
        node = node->next;
     
    if(node != NULL && node->value == value)
        return node;
     
    return NULL;
}
 
void Insert(int div, cell table[div], int value) {
    if(Search(div, table, value) == NULL) {
        unsigned int hash = Hash(value, div);
        cell *node = malloc(sizeof(cell));
         
        node->value = value;
        node->prev = &table[hash];
        node->next = table[hash].next;
        if(table[hash].next != NULL)
            table[hash].next->prev = node;
        table[hash].next = node;
    }
}
 
void Delete(int div, cell table[div], int value) {
    cell *node = Search(div, table, value);
    if(node != NULL) {
        node->prev->next = node->next;
        if(node->next != NULL)
            node->next->prev = node->prev;
    }
}
 
int main(int argc, const char * argv[]) {
    FILE *file = fopen("set.in","r");
    FILE *fileout = fopen("set.out","w");
     
    int div = 9973;
    int number;
    char oper[8];
    cell table[div];
    for(int i = 0; i < div; i++){
        table[i].next = NULL;
        table[i].prev = NULL;
    }
     
    fscanf(file, "%s", oper);
    fscanf(file, "%d", &number);
     
    while(feof(file) == 0) {
         
        if(strcmp(oper, "insert") == 0) {
            Insert(div, table, number);
        }
         
        if(strcmp(oper, "exists") == 0) {
            if(Search(div, table, number) != NULL)
                fprintf(fileout, "true\n");
            else
                fprintf(fileout, "false\n");
        }
         
        if(strcmp(oper, "delete") == 0) {
            Delete(div, table, number);
        }
         
        fscanf(file, "%s", oper);
        fscanf(file, "%d", &number);
    }
     
    fclose(fileout);
    fclose(file);
    
    return 0;
}
