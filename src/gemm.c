#include "gemm.h"


void gemm_nn(int m, int n, int k, float alpha, 
			 float* a, int la, 
			 float *b, int lb, 
			 float *c, int lc){

    int i,j,w;
    for(i=0; i<m; ++i){
        for(j=0; j<k; ++j){
            float a_elemet = alpha * a[i * la + j];
            for(w=0; w<n; ++w){
                c[i * lc + w] += a_elemet * b[j * lb + w];
            }
        }
    }

}