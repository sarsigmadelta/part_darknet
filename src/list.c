#include "list.h"
#include <stdio.h>

list* make_list(){
    list* l = (list*)malloc(sizeof(list));
    l->back = 0;
    l->front = 0;
    l->size = 0;
    return l;
}

void insert_list(list* l, void* data){
    node *n = (node*)malloc(sizeof(node));
    n->val = data;
    n->next = 0;
    
    if(!l->back){
        l->front = n;
        n->prev = 0;
    }else{
        n->prev = l->back;
        l->back->next = n;
    }
    l->back = n;
    ++l->size;
}


void show_list_int(list* l){
    node* f = l->front;
    int i;
    for(i=0; i<l->size; ++i){
        int *data = (int*)f->val;
        printf("%d\n", *data);
        f = f->next;
    }
}
