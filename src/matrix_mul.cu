#include "matrix_mul.h"
#include <cuda_runtime.h>
#include <cuda.h>


__global__ void vector_add(float *a, float *b){
    
}

void vector_add_called(float *a, float *b){
    dim3 blockSize(32, 32);
    dim3 gridSize(1, 1);
    vector_add<<<blockSize, gridSize>>>(a, b);
}