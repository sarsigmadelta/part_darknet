#ifndef IM2COL_H
#define IM2COL_H


float get_float_from_ptr(float *im, 
                         int channels, int height, int width,
                         int h, int w, int c);

void im2col(float *im, 
            int channels, int height, int width,
            int ksize, int stride, int pad, float *data_col);


#endif