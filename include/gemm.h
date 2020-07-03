#ifndef GEMM_H
#define GEMM_H

#include <stdio.h>
#include <stdlib.h>
#include <ctime>

void gemm_nn(int M, int N, int K, float alpha, 
			 float* a, int la, 
			 float *b, int lb, 
			 float *c, int lc);

void gemm_nt(int M, int N, int K, float alpha, 
			 float* a, int la, 
			 float *b, int lb, 
			 float *c, int lc);

void gemm_tn(int M, int N, int K, float alpha, 
			 float* a, int la, 
			 float *b, int lb, 
			 float *c, int lc);

void gemm_nn_col(int m, int n, int k, float alpha, 
			 float* a, int la, 
			 float *b, int lb, 
			 float *c, int lc);

void gemm_gpu_nn(int m, int n, int k, float alpha, 
			 	 float* a, int la, 
			 	 float *b, int lb, 
			 	 float *c, int lc);

float *rand_data(int m, int n);

void timing_for_gemm(void (*gemm_void)(int, int, int, float, float*, int,
								  float*, int, float*, int), 
								  int m, int n, int k, float alpha, 
								  float* a, int la, 
								  float *b, int lb, 
								  float *c, int lc);


#endif