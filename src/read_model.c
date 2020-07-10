#include "read_model.h"
#include "network.h"
#include "string.h"
#include "parse_utils.h"

convolution_layer parse_convolution_layer(size_param param, list *option){
    convolution_layer l = {0};
    int batch = param.batch;
    int width = param.w;
    int height = param.h;
    int channels = param.c;
    int filters = option_find_int(option, "filters");
    int pad = option_find_int(option, "pad");
    int stride = option_find_int(option, "stride");
    int ksize = option_find_int(option, "size");

    l = make_convolution_layer(batch, width, height, channels, ksize, filters, stride, pad);

    return l;
}

global_avg_layer parse_global_avg_layer(size_param param, list *option){
    global_avg_layer l = {0};
    int batch = param.batch;
    int width = param.w;
    int height = param.h;
    int channels = param.c;

    l = make_global_avg(batch, width, height, channels);
    return l;
}

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

network parse_network(char *filename){
    list *options = read_cfg(filename);
    network net = make_network(options->size - 1);
    node* n = options->front;
    list *net_param = ((section*)n->val)->option;
    size_param params = {0};
    params.batch = option_find_int(net_param, "batch");
    params.c = option_find_int(net_param, "channels");
    params.w = option_find_int(net_param, "width");
    params.h = option_find_int(net_param, "height");
    params.learning_rate = option_find_float(net_param, "learning_rate");

    net.width = params.w;
    net.height = params.h;
    net.channels = params.c;
    net.batch = params.batch;
    net.learning_rate = params.learning_rate;
    net.inputs = net.batch * net.height * net.width * net.channels;

    int idx_layer = 0;
    size_t workspace = 0;
    n = n->next;
    while(n){
        section *sec = (section*)n->val;
        char *type = sec->type;
        layer l = {0};
        if(!strcmp(type, "[convolutional]")){
            list *option = sec->option;
            l = parse_convolution_layer(params, option);
        }else if(!strcmp(type, "[global_avg]")){
            list *option = sec->option;
            l = parse_global_avg_layer(params, option);
        }
        n = n->next;
        if(n){
            params.c = l.out_c;
            params.h = l.out_h;
            params.w = l.out_w;
        }
        
        workspace = workspace > l.workspace ? workspace : l.workspace;
        net.layers[idx_layer] = l;
        idx_layer += 1;
    }
    net.n = idx_layer;
    net.outputs = net.layers[idx_layer-1].outputs * net.batch;
    net.output = net.layers[idx_layer-1].output;
    net.input = (float*)calloc(net.inputs, sizeof(float));
    net.workspace = (float*)malloc(workspace);

    return net;
}


