#include "load_data.h"
#include <opencv2/highgui.hpp>


image make_image(int height, int width, int channels){
    image im = {0};
    im.channels = channels;
    im.height = height;
    im.width = width;
    im.data = (float*)calloc(im.height * im.width * im.channels, sizeof(float));
    return im;
}

cv::Mat image_to_mat(image im){
    cv::Mat mat(im.height, im.width, CV_8UC3);
    int h,w,c;
    for(c=0; c<im.channels; ++c){
        for(h=0; h<im.height; ++h){
            uchar *data_ptr = mat.ptr<uchar>(h);
            for(w=0; w<im.width; ++w){
                int index = c * im.height * im.width + h * im.width + w;
                data_ptr[3*w + c] = im.data[index];
            }
        }
    }
    return mat;
}

image load_one_image(char *path){
    cv::Mat mat = cv::imread(path);
    int height = mat.rows;
    int width = mat.cols;
    int channels = mat.channels();
    image im = make_image(height, width, channels);

    int h,w,c;
    for(c=0; c<channels; ++c){
        for(h=0; h<height; ++h){
            uchar *data_ptr = mat.ptr<uchar>(h);
            for(w=0; w<width; ++w){
                int index = c * height * width + h * width + w;
                im.data[index] = data_ptr[3*w + c];
            }
        }
    }
    cv::Mat mat_c = image_to_mat(im);

    cv::imshow("test", mat_c);
    cv::waitKey(0);
    
    return im;
}

void* dummy_func(void* a){
    return 0;
}

pthread_t load_data(load_args args){
    load_args *ptr = (load_args*)calloc(1, sizeof(load_args));
    *ptr = args;
    pthread_t thread;
    pthread_create(&thread, 0, dummy_func, 0);
    return thread;
}