#ifndef READ_MODEL_H
#define READ_MODEL_H

#include "list.h"
#include <stdio.h>
#include <string.h>


char *read_line(FILE* fp);

list *read_cfg(char* file_path);

int read_options(list* l, char* line);

#endif