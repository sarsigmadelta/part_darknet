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
    int i;
    for(i=0; i<l.nweights; ++i){
        l.weight[i] = 1.;
    }
    l.weight_updates = (float*)calloc(l.nweights, sizeof(float));

    l.outputs = l.out_c * l.out_h * l.out_w;
    l.output = (float*)calloc(l.batch * l.outputs, sizeof(float));
    l.delta = (float*)calloc(l.batch * l.outputs, sizeof(float));
    l.bias = (float*)calloc(l.out_c, sizeof(float));
    l.bias_updates = (float*)calloc(l.out_c, sizeof(float));
    l.forward_cpu = forward_convolution_cpu;
    l.backward_cpu = backward_convolution_cpu;
    l.update_cpu = update_convolution_cpu;
    l.workspace = get_convolution_space(l);

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

void backward_convolution_cpu(layer l, network net){
    int m = l.out_c;
    int n = l.ksize * l.ksize * l.c;
    int k = l.out_h * l.out_w;

    int i;
    
    for(i=0; i<l.batch; ++i){
        float *a = l.delta + i * l.outputs;
        float *b = net.workspace;
        float *c = l.weight_updates;

        float *im = net.input + i * l.w * l.h * l.c;
        float *imd = net.delta + i * l.w * l.h * l.c;

        if(l.ksize==1){
            b = im;
        }else{
            im2col(im, l.c, l.h, l.w, l.ksize, l.stride, l.pad, b);
        }
        gemm_nt(m, n, k, 1., a, k, b, k, c, n);
        
        if(l.delta){
            float *a = l.weight;
            float *b = l.delta + + i * l.outputs;
            float *c = net.workspace;

            gemm_tn(n, k, m, 1., a, n, b, k, c, k);
            col2im(c, l.c, l.h, l.w, l.ksize, l.stride, l.pad, imd);
        }
        
    }
}

void update_convolution_cpu(layer l, update_param a){
    float learning_rate = a.learning_rate;
    axy_cpu(l.nweights, learning_rate, l.weight_updates, 1, l.weight, 1);
    axy_cpu(l.out_c, learning_rate, l.bias_updates, 1, l.bias, 1);
}