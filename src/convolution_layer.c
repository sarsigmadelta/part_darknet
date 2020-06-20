#include "convolution_layer.h"


int cal_out_h(int h, int ksize, int stride, int pad){
    return (h + 2 * pad - ksize) / stride + 1;
}



int cal_out_w(int w, int ksize, int stride, int pad){
    return (w + 2 * pad - ksize) / stride + 1;
}

size_t get_convolution_space(convolution_layer l){
    return l.ksize * l.ksize * l.c * l.out_w * l.out_h * sizeof(float);
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
    l.weight_updates = (float*)calloc(l.nweights, sizeof(float));

    l.outputs = l.out_c * l.out_h * l.out_w;
    l.output = (float*)calloc(l.batch * l.outputs, sizeof(float));
    l.bias = (float*)calloc(l.out_c, sizeof(float));
    l.bias_updates = (float*)calloc(l.out_c, sizeof(float));
    

    return l;
}

void forward_convolution_cpu(layer l, network net){
    int m = l.out_c;
    int k = l.ksize * l.ksize * l.c;
    int n = l.out_h * l.out_w;
    
    int i;
    for(i=0; i<l.batch; ++i){
        float *a = l.weight;
        float *im = net.input + i * l.w * l.h * l.c;
        float *b = net.workspace;
        float *c = l.output + i * l.outputs;
        if(l.ksize==1){
            b = im;
        }else{
            im2col(im, l.c, l.h, l.w, l.ksize, l.stride, l.pad, b);
        }
        gemm_nn(m, n, k, 1., a, k, b, n, c, n);
    }
    
}