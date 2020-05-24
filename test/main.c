#include "list.h"
#include "read_model.h"
#include <stdio.h>
#include <pthread.h>
#include "load_data.h"

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

int main(){

    char *path = "/home/mrzs/Proj/part_darknet/assets/trainImagePath.txt";
    //list *l = read_cfg(path);
    list *l = parse_pathes(path);
    char** pathes = paths_to_array(l);
    printf("%s\n", pathes[20]);
    printf("%d\n", l->size);

    char *image_path = "/home/mrzs/Desktop/d/jpgs/000001.jpg";
    char** pathes_picked = random_sample_pathes(pathes, 30, l->size);
    load_one_image_debug(pathes_picked[5], 256, 256);
    
    data buffer;
    load_args* args;
    args->paths = pathes;
    args->width = 512;
    args->height = 512;
    args->threads = 4;
    args->channels = 3;
    args->m = l->size;
    args->d = &buffer;

    pthread_t thread;
    pthread_create(&thread, 0, load_thread, args);
    pthread_join(thread, 0);
    return 0;
}

