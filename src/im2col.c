#include "im2col.h"
#include "list.h"

float get_float_from_ptr(float *im, 
                         int channels, int height, int width,
                         int h, int w, int c){
    if ((h >= height) | (w >= width)){
        return 0.;
    }
    int index = c * height * width + h * width + w;
    return im[index];
}



void im2col(float *im, 
            int channels, int height, int width,
            int ksize, int stride, int pad, float *data_col){
    
    int out_h = (height + 2*pad - ksize) / stride + 1;
    int out_w = (width + 2*pad - ksize) / stride + 1;
    int channels_cols = ksize * ksize * channels;
    data_col = (float*)calloc(channels_cols * out_h * out_w, sizeof(float));

    int h,w,c;
    for(c=0; c<channels_cols; ++c){
        int h_offset = c % ksize;
        int w_offset = c / ksize % ksize;
        int c_im = c / ksize / ksize;
        for(h=0; h<out_h; ++h){
            for(w=0; w<out_w; ++w){
                int h_im = h * stride + h_offset;
                int w_im = w * stride + w_offset;
                int index_col = c * out_h * out_w + h * out_w + w;
                data_col[index_col] = get_float_from_ptr(im, channels, height, width, h_im, w_im, c_im);
            }
        }
    }
}