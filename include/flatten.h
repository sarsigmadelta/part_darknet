#ifndef FLATTEN_H
#define FLATTEN_H

#include "darknet.h"

typedef layer flatten_layer;

flatten_layer make_flatten(int batch, int w, int h, int c);

void forward_flatten(layer l, network net);
void backward_flatten(layer l, network net);
void update_flatten(layer l, update_param a);


#endif