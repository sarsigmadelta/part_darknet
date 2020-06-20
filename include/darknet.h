#ifndef DARKNET_H
#define DARKNET_H

#include "list.h"


struct layer;
typedef struct layer layer;

struct network;
typedef struct network network;

struct layer{

    int w;
    int h;
    int c;

    int batch;

    int out_h;
    int out_w;
    int out_c;

    int ksize;
    int stride;
    int pad;

    int inputs;
    int outputs;
    int nweights;

    float *output;
    float *delta;

    float *weight;
    float *weight_updates;

    float *bias;
    float *bias_updates;

    void (*forward_convolution_cpu)(struct layer, struct network);
    void (*backward_convolution_cpu)(struct layer, struct network);
    void (*forward_convolution_gpu)(struct layer, struct network);
    void (*backward_convolution_gpu)(struct layer, struct network);

};

struct network{
    layer *layers;
    float *input;
    float *workspace;
    void (*forward_net)(struct network);
};



#endif