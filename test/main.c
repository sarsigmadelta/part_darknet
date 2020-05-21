#include "list.h"
#include "read_model.h"
#include <stdio.h>
#include <pthread.h>
#include "load_data.h"
#include "load_data_utils.h"

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

    char *image_path = "/home/mrzs/Desktop/d/jpgs/000001.jpg";
    load_one_image(image_path);

    pthread_t thread;
    pthread_create(&thread, 0, thread_func, 0);
    pthread_join(thread, 0);
    return 0;
}

