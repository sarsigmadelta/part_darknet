#ifndef MATRIX_MUL_SHARED_H
#define MATRIX_MUL_SHARED_H

#include <stdio.h>
#include <stdlib.h>

typedef struct mat{
    int height;
    int width;
    int stride;
    float *data;
}mat;

void matrix_mul_s_called(mat A, mat B, mat C);

mat get_random_mat(int h, int w){
    mat m = {0};
    m.height = h;
    m.width = w;
    m.stride = w;
    m.data = (float*)malloc(h * w  * sizeof(float));

    int i,j;
    for(i=0; i<h; ++i){
        for(j=0; j<w; ++j){
            int idx = i * w + j;
            m.data[idx] = rand()%1000/1000.;
        }
    }
    return m;
}

void test_matrix_mul_s();

mat golden_answer_cpu(mat a, mat b){
    mat c = {0};
    c.height = a.height;
    c.width = b.width;
    c.stride = b.stride;
    c.data = (float*)malloc(c.height * c.width * sizeof(float));
    int i, j, k;
    for(i=0; i<c.height; ++i){
        for(j=0; j<c.width; ++j){
            float cval = 0.;
            for(k=0; k<a.width; ++k){
                cval += a.data[i*a.width + k] * b.data[k*b.width + j];
            }
            c.data[i*c.width + j] = cval;
        }
    }
    return c;
}

void compare_result(mat a, mat b, mat c){
    mat golden = golden_answer_cpu(a, b);
    int i, j;
    for(i=0; i<c.height; ++i){
        for(j=0; j<c.width; ++j){
            int idx = i * c.width + j;
            if(c.data[idx] != golden.data[idx]){
                printf("c is not eq to golden\n");
                return;
            }
        }
    }
    printf("c is eq to golden!!!!\n");
}

#endif