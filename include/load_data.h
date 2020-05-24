#ifndef LOAD_DATA_H
#define LOAD_DATA_H

#include <pthread.h>
#include "load_data_utils.h"
#include <math.h>

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
    int m;
    
    data *d;
}load_args;



#ifdef __cplusplus
extern "C"{
#endif

    image load_one_image(char *path);
    image load_one_image_debug(char *path, int height_new, int width_new);
    image make_image(int height, int width, int channels);

    pthread_t load_data_in_thread(load_args args);
    void * load_threads(void* args);
    pthread_t load_data(load_args args);
    void* load_thread(void* args);

    float get_pixel_from_image(image im, int h, int w, int c);
    image resize_image(image im, int height_new, int width_new);

    data concat_data(data d1, data d2);
    data concat_datas(data* d, int n);
    matrix concat_matrix(matrix m1, matrix m2);
    char** random_sample_pathes(char** pathes, int n, int m);
    

#ifdef __cplusplus
}
#endif


#endif