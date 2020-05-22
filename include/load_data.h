#ifndef LOAD_DATA_H
#define LOAD_DATA_H

#include <pthread.h>

typedef struct image{
    int height;
    int width;
    int channels;
    float *data;
}image;

typedef struct matrix{
    int rows;
    int cols;
    float **data;
}matrix;

typedef struct data{
    matrix X;
    matrix y;
}data;

typedef struct load_args{
    int height;
    int width;
    int channels;

    char** paths;
    int threads;
    int n;

    
    data *d;
}load_args;



#ifdef __cplusplus
extern "C"{
#endif

    image load_one_image(char *path);
    image make_image(int height, int width, int channels);

    pthread_t load_data_in_thread(load_args args);
    void * load_threads(void* args);
    pthread_t load_data(load_args args);
    void* load_thread(void* args);

    data concat_data(data d1, data d2);
    data concat_datas(data* d, int n);
    matrix concat_matrix(matrix m1, matrix m2);

#ifdef __cplusplus
}
#endif


#endif