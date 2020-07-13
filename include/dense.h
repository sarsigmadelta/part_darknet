#ifndef DENSE_H
#define DENSE_H

#include "darknet.h"
#include "im2col.h"
#include "gemm.h"

typedef layer dense_layer;

dense_layer make_dense(int batch, int w, int h, int c);

void forward_dense(layer l, network net);
void backward_dense(layer l, network net);
void update_dense(layer l, update_param a);

#endif