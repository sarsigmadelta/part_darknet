#ifndef IM2COL_H
#define IM2COL_H
#include <stdio.h>
#include <stdlib.h>
#include "load_data.h"
#include "col2im.h"

float get_float_from_ptr(float *im, 
                         int channels, int height, int width,
                         int h, int w, int c);

void im2col(float *im, 
            int channels, int height, int width,
            int ksize, int stride, int pad, float *data_col);

void im2col_gpu(float *im, 
                int channels, int height, int width,
                int ksize, int stride, int pad, float *data_col);


void show_image(image *im);

image gen_random_image_test(int channels, int height, int width);

void show_im2col_result(image im, int ksize, int stride, int pad);

void show_im2col_gpu_result(image im, int ksize, int stride, int pad);


#endif