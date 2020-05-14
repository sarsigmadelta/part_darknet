#include "list.h"
#include "read_model.h"
#include <stdio.h>

// /home/jackliu/Proj/darknet_rep/assets/yolov2.cfg

int main(){

    list *l = make_list();
    char *path = "/home/jackliu/Proj/darknet_rep/assets/yolov2.cfg";
    read_cfg(path);
    return 0;
}