
#include "flatten.h"


flatten_layer make_flatten(int batch, int w, int h, int c){
    flatten_layer l = {0};
    l.w = w;
    l.h = h;
    l.c = c;
    l.batch = batch;
    l.inputs = l.w * l.h * l.c;
    l.outputs = l.inputs;
    l.output = (float*)calloc(l.batch * l.outputs, sizeof(float));
    l.delta = (float*)calloc(l.batch * l.outputs, sizeof(float));

    l.out_h = 1;
    l.out_w = 1;
    l.out_c = w*h*c;

    l.forward_cpu = forward_flatten;
    l.backward_cpu = backward_flatten;
    l.update_cpu = update_flatten;

    return l;
}

void forward_flatten(layer l, network net){
    int i,j,k;
    for(i=0; i<l.c; ++i){
        for(j=0; j<l.h; ++j){
            for(k=0; k<l.w; ++k){
                int idx = i * l.w * l.h + j * l.w + k;
                l.output[idx] = net.input[idx];
            }
        }
    } 
}

void backward_flatten(layer l, network net){
    int i,j,k;
    for(i=0; i<l.c; ++i){
        for(j=0; j<l.h; ++j){
            for(k=0; k<l.w; ++k){
                int idx = i * l.w * l.h + j * l.w + k;
                net.delta[idx] = l.delta[idx];
            }
        }
    } 
}

void update_flatten(layer l, update_param a){}