#include "col2im.h"

void col2im(float *data_col, 
            int channels, int height, int width,
            int ksize, int stride, int pad, float *im){
    int width_col = (width + 2 * pad - ksize) / stride + 1 ;
    int height_col = (height + 2 * pad - ksize) / stride + 1 ;
    int channels_col = ksize * ksize * channels ;
    int w,h,c;
    for(c=0; c<channels_col; ++c){
        int w_offset = c % ksize;
        int h_offset = c / ksize % ksize;
        int c_offset = c / ksize / ksize;
        for(h=0; h<height_col; ++h){
            for(w=0; w<width_col; ++w){
                int width_im = w * stride + w_offset;
                int height_im = h * stride + h_offset;
                int idx_im = c_offset * width * height + height_im * width + width_im;
                int idx_col = c * width_col * height_col + h * width_col + w;
                im[idx_im] += data_col[idx_col];
            }
        }
    }
}