#include "read_model.h"


/*
char *read_line(FILE* fp){
    int len = 128;
    char *line = calloc(len, sizeof(char));
    if(!fgets(line, len, fp)){
        return 0;
    }
    int len_new = strlen(line);
    line[len_new - 1] = '\0';
    return line;
}
*/



list *read_cfg(char* file_path){
    list *options = make_list();
    FILE *fp = fopen(file_path, "r");
    char *line = 0;

    section *current = 0;

 /*   while(line = read_line(fp)){
        switch(line[0]){
            case '[':
                current = calloc(1, sizeof(section));
                current->option = make_list();
                break;

            case '\n':
                break;
                
            case '\t':
                break;

            default:
                
        }
    }
*/
    return options;
}
