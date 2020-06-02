#ifndef IM2COL_H
#define IM2COL_H
#include <stdio.h>
#include <stdlib.h>
#include "load_data.h"


float get_float_from_ptr(float *im, 
                         int channels, int height, int width,
                         int h, int w, int c);

void im2col(float *im, 
            int channels, int height, int width,
            int ksize, int stride, int pad, float *data_col);

void show_image(image *im){
    int c, h, w;
    for(c=0; c<im->channels; ++c){
        for(h=0; h<im->height; ++h){
            for(w=0; w<im->width; ++w){
                int index = c*im->width*im->height + h*im->width + w;
                printf("%f ", im->data[index]);
            }
            printf("\n");
        }
        printf("\n");
    }
}

image gen_random_image(int channels, int height, int width){
    image im = make_image(height, width, channels);
    im.data = (float*)calloc(height*width*channels, sizeof(float));
    int c, h, w;
    for(c=0; c<channels; ++c){
        for(h=0; h<height; ++h){
            for(w=0; w<width; ++w){
                int index = c*im.width*im.height + h*im.width + w;
                im.data[index] = rand()%1000 / 1000. ;
            }
        }
    }
    return im;
}

void show_im2col_result(image im, int ksize, int stride, int pad);


#endif