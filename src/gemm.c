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

void gemm_nt(int m, int n, int k, float alpha, 
			 float* a, int la, 
			 float *b, int lb, 
			 float *c, int lc){
    
}

void gemm_tn(int m, int n, int k, float alpha, 
			 float* a, int la, 
			 float *b, int lb, 
			 float *c, int lc){
    
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

