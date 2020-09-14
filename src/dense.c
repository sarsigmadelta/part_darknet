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
    l.bias_updates = (float*)calloc(1, sizeof(float));

    l.forward_cpu = forward_dense;
    l.backward_cpu = backward_dense;
    l.update_cpu = update_dense;
    
    return l;
}

void forward_dense(layer l, network net){
    int m = l.batch;
    int k = l.inputs;
    int n = l.out_c;

    float *a = net.input;
    float *b = l.weight;
    float *c = l.output;

    gemm_nt(m, n, k, 1., a, k, b, k, c, n);
}

void backward_dense(layer l, network net){
    int i;

    int m = l.out_c;
    int k = l.batch;
    int n = l.inputs;

    float *a = l.delta;
    float *b = net.input;
    float *c = l.weight_updates;
            
    gemm_tn(m, n, k, 1., a, m, b, n, c, n);

    a = l.delta;
    b = l.weight;
    c = net.delta;

    m = l.batch;
    k = l.out_c;
    n = l.inputs;

    if(c){
        gemm_nt(m, k, n, 1, a, k, b, k, c, n);
    }
}

void update_dense(layer l, update_param a){
    float learning_rate = a.learning_rate;
    axy_cpu(l.nweights, learning_rate, l.weight_updates, 1, l.weight, 1);
    //axy_cpu(l.out_c, learning_rate, l.bias_updates, 1, l.bias, 1);
}



