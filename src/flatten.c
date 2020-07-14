
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

    l.forward_cpu = forward_flatten;

    return l;
}

void forward_flatten(layer l, network net){
    
}