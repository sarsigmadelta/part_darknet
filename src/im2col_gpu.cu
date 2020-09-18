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


__global__ void im2col_kernel(float *im, int channels, int height, int width, 
                              int ksize, int stride, int pad, int out_height, 
                              int out_width, float *data_col){

    int index = blockIdx.x * blockDim.x + threadIdx.x;
    int w_out = index % out_width;
    int h_out = index / out_width % out_height;
    int channel_in = index / out_width / out_height;
    int channel_out = channel_in * ksize * ksize;
    int w_in = w_out * stride - pad;
    int h_in = h_out * stride - pad;
    
    float *data_col_out = data_col;
    data_col_out += channel_out * out_height * out_width + h_out * out_width + w_out;

    const float *im_read = im + channel_in * height * width + h_in * width + w_in;

    int i,j;
    for(i=0; i<ksize; ++i){
        for(j=0; j<ksize; ++j){
            int h = h_in + i;
            int w = w_in + j;
            float val = get_float_from_ptr_gpu(im, channels, height, width, h, w, channel_in);
            *data_col_out = val;
            data_col_out += out_height * out_width;
        }
    }
}


void im2col_gpu(float *im, 
                int channels, int height, int width,
                int ksize, int stride, int pad, float *data_col){

    int out_height = (height + 2*pad - ksize) / stride + 1;
    int out_width = (width + 2*pad - ksize) / stride + 1;
    int channels_cols = ksize * ksize * channels;
    int totoal_threads = out_height * out_width * channels;

    int num_inputs = channels * height * width ; 
    int num_outputs = channels * ksize * ksize * out_height * out_width;
    float *im_d;
    float *data_col_d;

    cudaMallocManaged((void**)&im_d, num_inputs * sizeof(float));
    cudaMallocManaged((void**)&data_col_d, num_outputs * sizeof(float));

    cudaMemcpy(im_d, im, num_inputs * sizeof(float), cudaMemcpyHostToDevice);

    im2col_kernel<<<(totoal_threads + BLOCK_SIZE - 1)/BLOCK_SIZE, BLOCK_SIZE>>>(im, channels, height, 
                                                    width, ksize, stride, pad, out_height, out_width, 
                                                    data_col_d);

    cudaMemcpy(data_col, data_col_d, num_outputs * sizeof(float), cudaMemcpyDeviceToHost);


}


void show_im2col_gpu_result(image im, int ksize, int stride, int pad){
    printf("before im2col....\n");
    //show_image(&im);
    
    int out_h = (im.height + 2*pad - ksize) / stride + 1;
    int out_w = (im.width + 2*pad - ksize) / stride + 1;
    int channels_cols = ksize * ksize * im.channels;
    float *data_col = (float*)calloc(channels_cols * out_h * out_w, sizeof(float));

    im2col(im.data, 
            im.channels, im.height, im.width,
            ksize, stride, pad, data_col);
    
    printf("after im2col....\n");

/*    int i, j;
    for(i=0; i<channels_cols; ++i){
        for(int j=0; j<out_h * out_w; ++j){
            int index = i * out_h * out_w + j;
            printf("%f ", data_col[index]);
        }
        printf("\n");
    }
*/

}