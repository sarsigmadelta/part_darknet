#ifndef CONVOLUTION_LAYER_H
#define CONVOLUTION_LAYER_H

#include "darknet.h"

typedef layer convolution_layer;


int cal_out_h(int h, int ksize, int stride, int pad);
int cal_out_w(int w, int ksize, int stride, int pad);

convolution_layer make_convolution_layer(int batch, int w, int h, int c, int ksize, int filters, int stride, int pad);


#endif