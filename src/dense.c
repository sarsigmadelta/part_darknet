#include "dense.h"


dense_layer make_dense(int batch, int w, int h, int c, int out){
    dense_layer l = {0};
    l.batch = batch;
    l.h = h;
    l.w = w;
    l.c = c;
    l.out_c = out;
    l.out_h = 1;
    l.out_w = 1;
    l.inputs = l.h * l.w * l.c ;
    l.outputs = l.out_c * l.out_h * l.out_w;
    
    l.nweights = l.inputs * l.out_c;
    l.weight = (float*)calloc(l.nweights, sizeof(float));
    l.output = (float*)calloc(l.batch * l.outputs, sizeof(float));
    l.delta = (float*)calloc(l.batch * l.outputs, sizeof(float));

    l.weight_updates = (float*)calloc(l.nweights, sizeof(float));

    l.forward_cpu = forward_dense;
    
    return l;
}

void forward_dense(layer l, network net){
    int i;
    int m = 1;
    int k = l.inputs;
    int n = l.out_c;

    for(i=0; i<l.batch; ++i){
        float *a = net.input + i * l.inputs;
        float *b = l.weight;
        float *c = l.output + i * l.outputs;

        gemm_nn(m, n, k, 1., a, k, b, n, c, n);

    }
}

void backward_dense(layer l, network net){
    int i;

    for(i=0; i<l.batch; ++i){
        float *a = l.weight;
        float *b = l.delta;
        float *c = net.workspace;

        float *im = net.input;
        float *imd = net.delta;
        
        
        
        
    }
}



