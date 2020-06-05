#include "list.h"
#include "read_model.h"
#include <stdio.h>
#include <pthread.h>
#include "load_data.h"
#include "im2col.h"
#include "matrix_mul.h"

// /home/jackliu/Proj/darknet_rep/assets/yolov2.cfg
//trainImagePath

void show_options(list *l){
    int size = l->size;
    int i;
    node *f = l->front;
    for(i=0; i<size; ++i){
        kvp* k = (kvp*)f->val;
        printf("key is %s\t val is %s\n", k->key, k->val);
        f = f->next;
    }
    printf("------->-------------->\n");
}

void *thread_func(void* ptr){
    return 0;
}

#if 0
int main(){
    image im = gen_random_image(3,5,5);
    show_im2col_result(im, 3,1,0);
    //show_image(&im);
    return 0;
}
#endif


int main(){

    char *path = "/home/mrzs/Proj/part_darknet/assets/trainImagePath.txt";
    //list *l = read_cfg(path);
    list *l = parse_pathes(path);
    char** pathes = paths_to_array(l);
    printf("%s\n", pathes[8999]);
    printf("%d\n", l->size);

    char *image_path = "/home/mrzs/Desktop/d/jpgs/000001.jpg";
    char** pathes_picked = random_sample_pathes(pathes, 30, l->size - 1);
    image im_loaded = load_one_image_debug(pathes_picked[5], 256, 256);
    show_im2col_result(im_loaded, 3,1,0);
    data buffer;
    load_args args = {0};
    args.paths = pathes;
    args.width = 256;
    args.height = 256;
    args.threads = 4;
    args.channels = 3;
    args.m = l->size;
    args.d = &buffer;
    args.n = 64;
    pthread_t thread;
    thread = load_data(args);
    pthread_join(thread, 0);
    //show_float_ptr(args.d->X.data[63], args.height, args.width, args.channels);

    image_smooth_test(im_loaded);
    printf("%f, %f\n", im_loaded.data[100], im_loaded.data[300]);
    show_float_ptr(im_loaded.data, im_loaded.height, im_loaded.width, im_loaded.channels);
    float *a = (float*)calloc(10, sizeof(float));
    float *b = (float*)calloc(10, sizeof(float));
    vector_add_called(a, b);

    return 0;
}
