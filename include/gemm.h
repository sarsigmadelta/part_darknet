#ifndef GEMM_H
#define GEMM_H

#include <stdio.h>
#include <stdlib.h>

void gemm_nn(int m, int n, int k, int alpha, 
			 float* a, int la, 
			 float *b, int lb, 
			 float *c, int lc);


void gemm_gpu_nn(int m, int n, int k, int alpha, 
			 	 float* a, int la, 
			 	 float *b, int lb, 
			 	 float *c, int lc);




#endif