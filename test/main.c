#include "list.h"
#include "read_model.h"
#include <stdio.h>
#include "load_data.h"

// /home/jackliu/Proj/darknet_rep/assets/yolov2.cfg

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

int main(){

    char *path = "/home/mrzs/Proj/part_darknet/assets/yolov2.cfg";
    list *l = read_cfg(path);
    int n = l->size;
    int i;
    node *f = l->front;

    for(i=0; i<n; ++i){
        section *s = (section*)f->val;
        printf("type is %s\n", s->type);
        show_options(s->option);
        f = f->next;
    }

    char *image_path = "/home/mrzs/Desktop/d/jpgs/000001.jpg";
    load_one_image(image_path);

    return 0;
}