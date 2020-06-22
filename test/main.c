#include "list.h"
#include "read_model.h"
#include <stdio.h>
#include <pthread.h>
#include "load_data.h"
#include "im2col.h"
#include "matrix_mul.h"
#include "parse_utils.h"
#include "gemm.h"
#include "matrix_mul_shared.h"

void show_options(list *l){
    int size = l->size;
    int i;
    node *f = l->front;
    for(i=0; i<size; ++i){
        kvp* k = (kvp*)f->val;
        printf("key is %s\t val is %s\n", k->key, k->val);
        f = f->next;
    }
    printf("------->-------------->\n");
}

void show_model(list *l){
    int size = l->size;
    int i;
    node *f = l->front;
    section *current = (section*)f->val;
    printf("%s\n", current->type);
    char *momentum = option_find(current->option, "batch");
    printf("momentum is %s\n", momentum);
    while(f){
        section* current = (section*)f->val;
        char *type = current->type;
        list *options = current->option;
        printf("type is %s\n",type);
        show_options(options);
        f = f->next;
    }
}

void *thread_func(void* ptr){
    return 0;
}

float *get_random_data(int w, int h, int c){
    float *data = (float*)calloc(w*h*c, sizeof(float));
    int i;
    for(i=0; i<w*h*c; ++i){
        data[i] = rand()%1000/1000.;
    }
    return data;
}

int main(){
    char *cfg_path = "/home/mrzs/Proj/part_darknet/assets/yolov2_tiny.cfg";
    network net = parse_network(cfg_path);
    net.input = get_random_data(608,608,3);
    int i;
    for(i=0; i<608*608*3; ++i){
        printf("%f\n", net.input[i]);
    }
    
    return 0;
}
