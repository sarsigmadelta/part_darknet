#include "global_avg.h"

global_avg_layer make_global_avg(int batch, int w, int h, int c){
    global_avg_layer l = {0};
    l.w = w;
    l.h = h;
    l.c = c;
    l.out_c = c;
    l.out_h = 1;
    l.out_w = 1;
    l.outputs = l.out_c;
    l.batch = batch;
    l.inputs = l.batch * l.h * l.w * l.c;

    l.output = (float*)calloc(l.batch * l.outputs, sizeof(float));
    l.delta = (float*)calloc(l.batch * l.outputs, sizeof(float));

    l.forward_cpu = forward_global_gvg;
    l.backward_cpu = backward_global_gvg;
    l.update_cpu = update_global_avg;

    return l;
}

void forward_global_gvg(layer l, network net){
    int i;
    for(i=0; i<l.batch; ++i){
        float *a = net.input + i * l.w * l.h * l.c;
        int m,n,k;
        for(m=0; m<l.c; ++m){
            float scale = l.w * l.h;
            for(n=0; n<l.h; ++n){
                for(k=0; k<l.w; ++k){
                    int idx = m * l.w * l.h + n * l.w + k;
                    l.output[m] += net.input[idx];
                }
            }
            l.output[m] /= scale;
        }
    }
}


void backward_global_gvg(layer l, network net){

    int b, i, j, k;
    for(b=0; b<l.batch; ++b){
        float *imd = net.delta + b * l.c * l.h * l.w;
        float *delb = l.delta + b * l.c * l.h * l.w;
        for(i=0; i<l.c; ++i){
            for(j=0; j<l.h; ++j){
                for(k=0; k<l.w; ++k){
                    int idx = i * l.h * l.w + j * l.w + k;
                    imd[idx] = delb[i];
                }
            }
        }
    }
}

void update_global_avg(layer l, update_param a){

}