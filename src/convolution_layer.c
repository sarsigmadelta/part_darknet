#include "convolution_layer.h"


int cal_out_h(int h, int ksize, int stride, int pad){
    return (h + 2 * pad - ksize) / stride + 1;
}



int cal_out_w(int w, int ksize, int stride, int pad){
    return (w + 2 * pad - ksize) / stride + 1;
}

convolution_layer make_convolution_layer(int batch, int w, int h, int c, int ksize, int filters, int stride, int pad){
    convolution_layer l = {0};
    l.w = w;
    l.h = h;
    l.c = c;
    l.batch = batch;

    l.ksize = ksize;
    l.stride = stride;
    l.pad = pad;

    l.out_c = filters;
    l.out_h = cal_out_h(h, ksize, stride, pad);
    l.out_w = cal_out_w(w, ksize, stride, pad);

    l.nweights = (l.ksize * l.ksize * l.c) * l.out_c;
    l.weight = (float*)calloc(l.nweights, sizeof(float));

    l.outputs = l.batch * l.out_c * l.out_h * l.out_w;
    l.output = (float*)calloc(l.outputs, sizeof(float));
    l.bias = (float*)calloc(l.out_c, sizeof(float));
    

    return l;
}