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
#include "network.h"

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

void gen_random_delta(network* net){
    int n = net->n;
    layer l = net->layers[n-1];
    l.delta = (float*)calloc(l.outputs, sizeof(float));
    int i;
    for(i=0; i<l.outputs; ++i){
        l.delta[i] = (float)(rand() % 10000) / 10000.;
    }
    net->layers[n-1].delta = l.delta;
}

int main(){
    char *cfg_path = "/part_darknet/assets/yolov2_tiny.cfg";
    network net = parse_network(cfg_path);
    net.input = get_random_data(608,608,3);

    int i;
    for(i=0; i<net.n; ++i){
        layer l = net.layers[i];
        printf("out_h is %d\tout_w is %d\tout_c is %d\n",l.out_h,l.out_w,l.out_c);
    }

    
    for(i=0; i<5; ++i){
        forward_network(&net);
        gen_random_delta(&net);
        backward_network(&net);
        update_network(&net);
    }

    printf("net.ouput[-1] is %f\n", net.layers[net.n-1].output[net.layers[net.n-1].outputs-1]);
    printf("net.delta[-1] is %f\n", net.layers[0].delta[net.layers[0].outputs-1]);
    printf("net.ouput[64] is %f\n", net.layers[net.n-1].output[64]);
    printf("net.delta[64] is %f\n", net.layers[0].delta[63]);
    
    return 0;
}
