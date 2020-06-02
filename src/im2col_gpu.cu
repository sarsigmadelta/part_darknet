#include "im2col.h"


#define BLOCK_SIZE 256

__device__ float get_float_from_ptr_gpu(float *im, 
                                        int channels, int height, int width,
                                        int h, int w, int c){
    if ((h >= height) | (w >= width)){
        return 0.;
    }
    int index = c * height * width + h * width + w;
    return im[index];
}


__global__ void im2col_kernel(){
    
}

void im2col_gpu(float *im, 
                int channels, int height, int width,
                int ksize, int stride, int pad, float *data_col){

    int out_h = (height + 2*pad - ksize) / stride + 1;
    int out_w = (width + 2*pad - ksize) / stride + 1;
    int channels_cols = ksize * ksize * channels;
    int totoal_threads = out_h * out_w * channels_cols;
    

}