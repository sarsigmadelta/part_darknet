#ifndef READ_MODEL_H
#define READ_MODEL_H

#include "list.h"
#include <stdio.h>
#include <string.h>
#include "darknet.h"
#include "convolution_layer.h"
#include "global_avg.h"
#include "flatten.h"
#include "dense.h"

char *read_line(FILE* fp);

list *read_cfg(char* file_path);

int read_options(list* l, char* line);

network parse_network(char *filename);

convolution_layer parse_convolution_layer(size_param param, list *l);

flatten_layer parse_flatten_layer(size_param param, list *option);

dense_layer parse_dense_layer(size_param param, list *option);

#endif