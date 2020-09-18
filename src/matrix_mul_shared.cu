#include "matrix_mul_shared.h"
#include "cuda_runtime.h"
#include <cuda.h>

#define BLOCK_SIZE 16

__device__ float get_element(mat m, int row, int col){
    return m.data[row * m.stride + col];
}

__device__ void set_element(mat m, int row, int col, float val){
    m.data[row * m.stride + col] = val;
}

__device__ mat get_sub_matrix(mat m, int row, int col){
    mat sub_m;
    sub_m.height = BLOCK_SIZE;
    sub_m.width = BLOCK_SIZE;
    sub_m.stride = m.stride;
    sub_m.data = &m.data[m.stride * row * BLOCK_SIZE + col * BLOCK_SIZE];
    return sub_m;
}

__global__ void matrix_mul_kernel(mat a, mat b, mat c){
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    int i;
    float cval = 0.;
    for(i=0; i<a.width; ++i){
        cval += a.data[row * a.width + i] * b.data[i * b.width + col];
    }
    set_element(c, row, col, cval);
}

__global__ void matrix_mul_s_kernel(mat a, mat b, mat c){
    int bx = blockIdx.x;
    int by = blockIdx.y;

    int tx = threadIdx.x;
    int ty = threadIdx.y;

    mat c_sub = get_sub_matrix(c, by, bx);

    float Cval = 0.;
    int m;
    for(m=0; m<a.height / BLOCK_SIZE; ++m){
        mat a_sub = get_sub_matrix(a, by, m);
        mat b_sub = get_sub_matrix(b, m, bx);

        __shared__ float sub_as[BLOCK_SIZE][BLOCK_SIZE];
        __shared__ float sub_bs[BLOCK_SIZE][BLOCK_SIZE];

        sub_as[ty][tx] = get_element(a_sub, ty, tx);
        sub_bs[ty][tx] = get_element(b_sub, ty, tx);
        
        __syncthreads();

        for(int e=0; e<BLOCK_SIZE; ++e){
            Cval += sub_as[ty][e] * sub_bs[e][tx];
        }

    }
    set_element(c_sub, ty, tx, Cval);
}

void matrix_mul_s_called(mat A, mat B, mat C){
    mat *d_A, *d_B, *d_C;

    size_t size_A = A.width * A.height * sizeof(float);
    size_t size_B = B.width * B.height * sizeof(float);
    size_t size_C = C.width * C.height * sizeof(float);

    cudaMallocManaged((void**)&d_A, sizeof(mat));
    cudaMallocManaged((void**)&d_B, sizeof(mat));
    cudaMallocManaged((void**)&d_C, sizeof(mat));

    cudaMallocManaged((void**)&d_A->data, size_A);
    cudaMallocManaged((void**)&d_B->data, size_B);
    cudaMallocManaged((void**)&d_C->data, size_C);

    d_A->height = A.height;
    d_A->width = A.width;
    d_A->stride = A.stride;

    d_B->height = B.height;
    d_B->width = B.width;
    d_B->stride = B.stride;

    d_C->height = C.height;
    d_C->width = C.width;
    d_C->stride = C.stride;

    cudaMemcpy(d_A->data, A.data, size_A, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B->data, B.data, size_B, cudaMemcpyHostToDevice);

    dim3 blockSize(BLOCK_SIZE, BLOCK_SIZE);
    dim3 gridSize( (C.height + BLOCK_SIZE - 1) / BLOCK_SIZE,    (C.width + BLOCK_SIZE - 1) / BLOCK_SIZE);

    //matrix_mul_s_kernel<<<gridSize, blockSize>>>(*d_A, *d_B, *d_C);
    matrix_mul_kernel<<<gridSize, blockSize>>>(*d_A, *d_B, *d_C);

    cudaMemcpy(C.data, d_C->data, size_C, cudaMemcpyDeviceToHost);
    
}

void test_matrix_mul_s(){
    int height = 1024;
    int width = 1024;
    
    mat a = get_random_mat(height, width);
    mat b = get_random_mat(height, width);
    mat c = get_random_mat(height, width);

    matrix_mul_s_called(a, b, c);
    compare_result(a, b, c);

}
