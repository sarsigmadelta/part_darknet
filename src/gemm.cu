#include "gemm.h"
#include "cuda_runtime.h"
#include <cuda.h>

#define BLOCKSIZE 16

__global__ void gemm_nn_kernel( int m, int n, int k, int alpha, 
			 	                float* a, int la, 
			 	                float *b, int lb, 
			 	                float *c, int lc){

    int col = blockIdx.x * blockDim.x + threadIdx.x;
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int i;
    float sum = 0.;
    for(i=0; i<k; ++i){
        sum += alpha * a[row * la + k] * b[k * lb + col];
    }
    c[row * lc + col] = sum;
}


void gemm_gpu_nn(int m, int n, int k, int alpha, 
			 	 float* a, int la, 
			 	 float *b, int lb, 
			 	 float *c, int lc){
    float *d_a, *d_b, *d_c;
    size_t size_a = m * k * sizeof(float);
    size_t size_b = k * n * sizeof(float);
    size_t size_c = m * n * sizeof(float);

    cudaMallocManaged((void**)&d_a, size_a);
    cudaMallocManaged((void**)&d_b, size_b);
    cudaMallocManaged((void**)&d_c, size_c);

    cudaMemcpy(d_a, a, size_a, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, size_b, cudaMemcpyHostToDevice);

    dim3 blockSize(BLOCKSIZE, BLOCKSIZE);
    dim3 gridSize((m + BLOCKSIZE - 1)/BLOCKSIZE, (n + BLOCKSIZE - 1)/BLOCKSIZE);

    gemm_nn_kernel<<<gridSize, blockSize>>>(m, n, k, alpha, d_a, la, d_b, lb, d_c, lc);
    cudaMemcpy(c, d_c, size_c, cudaMemcpyDeviceToHost);
    
}