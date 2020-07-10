#ifndef GLOBAL_AVG_H
#define GLOBAL_AVG_H


#include "darknet.h"
#include "im2col.h"
#include "gemm.h"


typedef layer global_avg_layer;


global_avg_layer make_global_avg(int batch, int w, int h, int c);

void forward_global_gvg(layer l, network net);
void backward_global_gvg(layer l, network net);
void update_global_avg(layer l, update_param a);


#endif