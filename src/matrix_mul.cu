#include "matrix_mul.h"
#include <cuda_runtime.h>
#include <cuda.h>


__global__ void vector_add(float *a, float *b){
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    a[i] += b[i];
}

__global__ void pixel_remove(image* im){
    int col = threadIdx.x + blockIdx.x * blockDim.x;
    int row = threadIdx.y + blockIdx.y * blockDim.y;
    int c = 0;
    for(c=0; c<im->channels; ++c){
        int index = c * im->height * im->width + row * im->width + col;
        im->data[index] = 0.1;
    }
}

void vector_add_called(float *a, float *b){
    dim3 blockSize(1, 1);
    dim3 gridSize(1, 1);
    vector_add<<<blockSize, gridSize>>>(a, b);
}

void image_smooth_test(image im){
    size_t nBytes = im.height * im.width * im.channels * sizeof(float);
    image *im_d ;
    cudaMallocManaged((void**)&im_d, sizeof(image));
    im_d->width = im.width;
    im_d->height = im.height;
    im_d->channels = im.channels;
    
    cudaMallocManaged((void**)&im_d->data, nBytes);
    cudaMemcpy(im_d->data, im.data, nBytes, cudaMemcpyHostToDevice);

    dim3 blockSize(16, 16);
    dim3 gridSize(16, 16);
    
    pixel_remove<<<gridSize,  blockSize>>>(im_d);

    cudaMemcpy(im.data, im_d->data, nBytes, cudaMemcpyDeviceToHost);
    
}
