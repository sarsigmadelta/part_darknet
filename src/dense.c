#include "dense.h"


dense_layer make_dense(int batch, int w, int h, int c){
    dense_layer l = {0};
    l.batch = batch;
    l.h = h;
    l.w = w;
    l.c = c;
    l.inputs = l.h * l.w * l.c ;
    
    return l;
}

