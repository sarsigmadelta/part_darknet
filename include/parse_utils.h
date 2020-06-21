#ifndef PARSE_UTILS_H
#define PARSE_UTILS_H

#include "list.h"
#include <string.h>

char *option_find(list *l, char *key){
    node *n = l->front;
    while(n){
        kvp *k = (kvp*)n->val;
        if(!strcmp(k->key, key)){
            k->used = 1;
            return k->val;
        }
        n = n->next;
    }
    return 0;
}

int option_find_int(list *l, char *key){
    node *n = l->front;
    while(n){
        kvp *k = (kvp*)n->val;
        if(!strcmp(k->key, key)){
            k->used = 1;
            return atoi(k->val);
        }
        n = n->next;
    }
    return 0;
}




#endif