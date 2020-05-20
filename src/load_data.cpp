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


image load_one_image(char *path){
    cv::Mat mat = cv::imread(path);
    int height = mat.rows;
    int width = mat.cols;
    int channels = mat.channels();
    image im = make_image(height, width, channels);
    

    cv::imshow("test", mat);
    cv::waitKey(0);
    
    return im;
}