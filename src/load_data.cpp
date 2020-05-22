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


void* load_thread(void* args){

}

pthread_t load_data_in_thread(load_args args){
    pthread_t thread;
    load_args* ptr = (load_args*)calloc(1, sizeof(load_args));
    *ptr = args;
    pthread_create(&thread, 0, load_thread, ptr);
    return thread;
}

void * load_threads(void* args){
    load_args ptr = *(load_args*)args;
    if(ptr.threads==0){
        ptr.threads = 1;
    }

    int total = ptr.n;
    data *out = ptr.d;
    data* buffers = (data*)calloc(ptr.threads, sizeof(data));
    pthread_t *threads = (pthread_t*)calloc(ptr.threads, sizeof(pthread_t));
    int i;
    
    for(i=0; i<ptr.threads; ++i){
        ptr.d = buffers + i;
        ptr.n = (i+1) * total / ptr.threads - i * total / ptr.threads ;
        threads[i] = load_data_in_thread(ptr);
    }
    
    for(i=0; i<ptr.threads; ++i){
        pthread_join(threads[i], 0);
    }
    
}

pthread_t load_data(load_args args){
    load_args *ptr = (load_args*)calloc(1, sizeof(load_args));
    *ptr = args;
    pthread_t thread;
    pthread_create(&thread, 0, load_threads, ptr);
    return thread;
}


matrix concat_matrix(matrix m1, matrix m2){
    matrix m = {0};
    m.rows = m1.rows + m2.rows;
    m.cols = m1.cols;
    m.data = (float**)calloc(m.rows, sizeof(float*));
    int i;
    for(i=0; i<m1.rows; ++i){
        m.data[i] = m1.data[i];
    }
    for(i=m1.rows; i<m.rows; ++i){
        m.data[i] = m2.data[i-m1.rows];
    }
    return m;
}

data concat_data(data d1, data d2){
    data d = {0};
    d.X = concat_matrix(d1.X, d2.X);
    d.y = concat_matrix(d1.y, d2.y);
    return d;
}


data concat_datas(data* d, int n){
    data out = {0};
    int i;
    for(i=0; i<n; ++i){
        data new_ = concat_data(d[i], out);
        out = new_;
    }
    return out;
}