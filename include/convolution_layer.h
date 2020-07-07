#ifndef CONVOLUTION_LAYER_H
#define CONVOLUTION_LAYER_H

#include "darknet.h"
#include "im2col.h"
#include "gemm.h"


typedef layer convolution_layer;


int cal_out_h(int h, int ksize, int stride, int pad);
int cal_out_w(int w, int ksize, int stride, int pad);

convolution_layer make_convolution_layer(int batch, int w, int h, int c, int ksize, int filters, int stride, int pad);

void forward_convolution_cpu(layer l, network net);
void backward_convolution_cpu(layer l, network net);
void update_convolution_cpu(layer l, update_param a);

#endif