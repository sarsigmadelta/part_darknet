#include "im2col.h"
#include "list.h"

float get_float_from_ptr(float *im, 
                         int channels, int height, int width,
                         int h, int w, int c){
    if ((h >= height) | (w >= width)){
        return 0.;
    }
    int index = c * height * width + h * width + w;
    return im[index];
}



void im2col(float *im, 
            int channels, int height, int width,
            int ksize, int stride, int pad, float *data_col){
    
    int out_h = (height + 2*pad - ksize) / stride + 1;
    int out_w = (width + 2*pad - ksize) / stride + 1;
    int channels_cols = ksize * ksize * channels;
    //data_col = (float*)calloc(channels_cols * out_h * out_w, sizeof(float));

    int h,w,c;
    for(c=0; c<channels_cols; ++c){
        int h_offset = c % ksize;
        int w_offset = c / ksize % ksize;
        int c_im = c / ksize / ksize;
        for(h=0; h<out_h; ++h){
            for(w=0; w<out_w; ++w){
                int h_im = h * stride + h_offset;
                int w_im = w * stride + w_offset;
                int index_col = c * out_h * out_w + h * out_w + w;
                data_col[index_col] = get_float_from_ptr(im, channels, height, width, h_im, w_im, c_im);
            }
        }
    }
}

image gen_random_image_test(int channels, int height, int width){
    image im = make_image(height, width, channels);
    im.data = (float*)calloc(height*width*channels, sizeof(float));
    int c, h, w;
    for(c=0; c<channels; ++c){
        for(h=0; h<height; ++h){
            for(w=0; w<width; ++w){
                int index = c*im.width*im.height + h*im.width + w;
                im.data[index] = (float)(rand()%100000) / 100000. ;
            }
        }
    }
    return im;
}

void show_im2col_result(image im, int ksize, int stride, int pad){
    printf("before im2col....\n");
    show_image(&im);
    
    int out_h = (im.height + 2*pad - ksize) / stride + 1;
    int out_w = (im.width + 2*pad - ksize) / stride + 1;
    int channels_cols = ksize * ksize * im.channels;
    float *data_col = (float*)calloc(channels_cols * out_h * out_w, sizeof(float));
    image im_cpy = gen_random_image_test(im.channels, im.height, im.width);
    memset(im_cpy.data, 0, im_cpy.channels * im_cpy.height * im_cpy.width * sizeof(float));

    im2col(im.data, 
            im.channels, im.height, im.width,
            ksize, stride, pad, data_col);
    
    printf("after im2col....\n");

    int i, j;
    for(i=0; i<channels_cols; ++i){
        for(int j=0; j<out_h * out_w; ++j){
            int index = i * out_h * out_w + j;
            printf("%f ", data_col[index]);
        }
        printf("\n");
    }

    col2im(data_col, im.channels, im.height, im.width, ksize, stride, pad, im_cpy.data);

    printf("after col2im again....\n");
    show_image(&im_cpy);
}

void show_image(image *im){
    int c, h, w;
    for(c=0; c<im->channels; ++c){
        for(h=0; h<im->height; ++h){
            for(w=0; w<im->width; ++w){
                int index = c*im->width*im->height + h*im->width + w;
                printf("%f ", im->data[index]);
            }
            printf("\n");
        }
        printf("\n");
    }
}