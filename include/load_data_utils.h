#ifndef LOAD_DATA_UTILS_H
#define LOAD_DATA_UTILS_H

#include "list.h"
#include <stdio.h>
#include <string.h>



list *parse_pathes(char* file_path);

char** paths_to_array(list *l);

#endif