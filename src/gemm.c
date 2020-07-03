#include "gemm.h"

void gemm_nn(int M, int N, int K, float alpha, 
			 float* a, int la, 
			 float *b, int lb, 
			 float *c, int lc){
    int i,j,k;
    for(i=0; i<M; ++i){
        for(k=0; k<K; ++k){
            float a_t = alpha * a[i*la + k];
            for(j=0; j<N; ++j){
                c[i*lc + j] += a_t * b[k * lb + j];
            }
        }
    }
}

void gemm_nt(int M, int N, int K, float alpha, 
			 float* a, int la, 
			 float *b, int lb, 
			 float *c, int lc){
    int i,j,k;
    for(i=0; i<M; ++i){
        for(j=0; j<N; ++j){
            for(k=0; k<K; ++k){
                c[i*lc + j] += alpha * a[i*lc + k] + b[j*lb + k];
            }
        }
    }
}

void gemm_tn(int M, int N, int K, float alpha, 
			 float* a, int la, 
			 float *b, int lb, 
			 float *c, int lc){
    int i,j,k;
    for(i=0; i<M; ++i){
        for(k=0; k<K; ++k){
            float a_t = a[k*la + i];
            for(j=0; j<N; ++j){
                c[i*lc + j] += a_t * b[k * lb + j];
            }
        }
    }
}

void gemm_nn_col(int m, int n, int k, float alpha, 
			 float* a, int la, 
			 float *b, int lb, 
			 float *c, int lc){
    int i, j, w;
    for(i=0; i<m; ++i){
        for(j=0; j<n; ++j){
            float sum = 0.;
            for(w=0; w<k; ++w){
                sum += alpha * a[i*la+w] * b[w*lc + j];
            }
            c[i*lc + j];
        }
        
    }
}


void timing_for_gemm(void (*gemm_void)(int, int, int, float, float*, int,
								  float*, int, float*, int), 
								  int m, int n, int k, float alpha, 
								  float* a, int la, 
								  float *b, int lb, 
								  float *c, int lc){
    clock_t clock_start = clock();
    gemm_void(m, n, k, alpha, a, la, b, lb, c, lc);
    clock_t clock_end = clock();
    double time = double(clock_end - clock_start ) / CLOCKS_PER_SEC;
    printf("timing of gemm_void is %f\n", time);
}

float *rand_data(int m, int n){
    int i, j;
    float *data = (float*)calloc(m * n, sizeof(float));
    if(!data){
        printf("float ptr malloc failed...\n");
        return 0;
    }
    srand(time(NULL));
    for(i=0; i<m; ++i){
        for(j=0; j<n; ++j){
            float v = rand()%10000/10000.;
            int index = i * n + j;
            data[index] = v;
        }
    }
    return data;
}

