#include "read_model.h"



char *read_line(FILE* fp){
    int len = 128;
    char *line = (char*)calloc(len, sizeof(char));
    if(!fgets(line, len, fp)){
        return 0;
    }
    int len_new = strlen(line);
    line[len_new - 1] = '\0';
    return line;
}

int read_options(list* l, char* line){
    char *key = 0;
    char *val = 0;
    kvp *k = (kvp*)calloc(1, sizeof(kvp));
    int size = strlen(line);
    if(size==0){
        return 1;
    }
    key = line;
    int i = 0;

    for(i=0; i<size; ++i){
        if(line[i] == '='){
            val = &line[i+1];
            key[i] = '\0';
            break;
        }
    }
    k->val = val;
    k->key = key;
    k->used = 0;

    insert_list(l, k); 
    return 1;
}


list *read_cfg(char* file_path){
    list *options = make_list();
    FILE *fp = fopen(file_path, "r");
    char *line = 0;

    section *current = 0;

    while(line = read_line(fp)){
        switch(line[0]){
            case '[':
                current = (section*)calloc(1, sizeof(section));
                current->option = make_list();
                current->type = line; 
                insert_list(options, current);
                break;

            case '\n':
                break;
                
            case '\t':
                break;

            case '#':
                break;

            default:
                if(read_options(current->option, line)){
                }
                break;
        }
    }
    return options;
}
