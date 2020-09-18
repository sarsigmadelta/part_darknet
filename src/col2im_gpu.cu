#include "col2im.h"

const int blockSize = 512;


__global__ void col2im_gpu_kernel(float *data_col, int channels, int height, int width,
                            int ksize, int stride, int pad, 
                            int height_col, int width_col, float *im){
    int idx = blockDim.x * blockIdx.x + threadIdx.x;
    int 
}


void col2im_gpu(float *data_col, 
            int channels, int height, int width,
            int ksize, int stride, int pad, float *im){
    int height_col = (height - ksize + 2*pad)/stride + 1;
    int width_col = (width - ksize + 2*pad)/stride + 1;
    int num_threads = height * width * channels;
    col2im_gpu_kernel<<<(num_threads + blockSize -1 )/blockSize, blockSize>>>(data_col, channels, height, width,
                                                ksize, stride, pad, height_col, width_col, im);
}