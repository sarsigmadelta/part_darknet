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

    size_t workspace;

    void (*forward_cpu)(struct layer, struct network);
    void (*backward_cpu)(struct layer, struct network);
    void (*forward_gpu)(struct layer, struct network);
    void (*backward_gpu)(struct layer, struct network);

};

struct network{
    layer *layers;
    int inputs;
    float *input;
    float *workspace;
    float *output;
    void (*forward_net)(struct network);
    int n;
};

typedef struct size_param{
    int w;
    int h;
    int c;
    int batch;
    network *net;
    int outputs;
}size_param;


#endif