#include "col2im.h"

const int blockSize = 512;


__global__ void col2im_gpu_kernel(float *data_col, int channels, int height, int width,
                            int ksize, int stride, int pad, 
                            int height_col, int width_col, float *im){
    int index = blockDim.x * blockIdx.x + threadIdx.x;
    int w_im = index % width;
    int h_im = index / width % height;
    int c_im = index / width / height;
    
    int w_col_start = ( w_im < ksize) ? 0 : (w_im - ksize) / stride + 1;
    int w_col_end = min(w_im / stride + 1, width_col);
    int h_col_start = (h_im < ksize ) ? 0 : (h_im - ksize) / stride + 1;
    int h_col_end = min(h_im / stride + 1, height_col);

    int h_col, w_col;
    for(h_col=h_col_start; h_col<h_col_end; ++h_col){
        for(w_col=w_col_start; w_col<w_col_end; ++w_col){
            int w_k = h_im - h_col * stride;
            int h_k = w_im - w_col * stride;
            int index_col = (c_im * ksize * ksize + h_k * ksize + w_k) * height_col * width_col + h_col * width_col + w_col;
            im[index] += data_col[index_col];
        }
    }
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