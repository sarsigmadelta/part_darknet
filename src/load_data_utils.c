#include "load_data_utils.h"


list *parse_pathes(char* file_path){
    list *l = make_list();
    FILE *fp = fopen(file_path, "r");
    int line_size = 512;
    char *line = (char*)calloc(line_size, sizeof(char));
    while(fgets(line, line_size, fp)){
        line[strlen(line) - 1] = '\0';
        insert_list(l, line);
    }
    return l;
}

char** paths_to_array(list *l){
    int n = l->size;
    int i;
    char **pathes = (char**)calloc(n, sizeof(char*));
    node* front = l->front;
    for(i=0; i<n; ++i){
        pathes[i] = (char*)front->val;
        front = front->next;
    }
    return pathes;
}

void axy_cpu(int N, float ALPHA, float *x, int INCX, float *y, int INCY){
    int i;
    for(i=0; i<N; ++i){
        x[i*INCX] += y[i*INCY] * ALPHA;
    }
}

