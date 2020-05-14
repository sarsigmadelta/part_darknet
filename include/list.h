#ifndef LIST_H
#define LIST_H

#include <stdlib.h>


typedef struct node{
    struct node* prev;
    struct node* next;
    void *val;
}node;

typedef struct list{
    node* back;
    node* front;
    int size;
}list;

typedef struct section{
    char *type;
    list *option;
}section;


list* make_list();

void insert_list(list* l, void* data);

void show_list_int(list* l);


#endif