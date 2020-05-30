#include "matrix_mul.h"
#include <cuda_runtime.h>
#include <cuda.h>


__global__ void vector_add(float *a, float *b){
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    a[i] += b[i];
}

__global__ void pixel_remove(image* im){
    int idx_x = threadIdx.x + blockDim.x * blockDim.x;
    int idx_y = threadIdx.y + blockDim.y * blockDim.y;
    int index = idx_y * im->width + idx_x;
    im->data[index] *= 0.0;
    //printf("im->data[index] %f\n", im->data[index]);
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
    cudaMallocManaged((void**)&im_d->data, nBytes);
    cudaMemcpy(im_d->data, im.data, nBytes, cudaMemcpyHostToDevice);

    dim3 blockSize(16, 16);
    dim3 gridSize(16, 16);
    
    pixel_remove<<<gridSize,  blockSize>>>(im_d);

    cudaMemcpy(im.data, im_d->data, nBytes, cudaMemcpyDeviceToHost);
    
}
