cmake_minimum_required(VERSION 3.2)

PROJECT(build_darknet)

set(CMAKE_C_FLAGS "-pthread")
set(CMAKE_CXX_FLAGS "-fPIC" )

SET(CMAKE_C_COMPILER g++)
add_compile_options(-std=c++11)
add_compile_options(-g)

INCLUDE_DIRECTORIES(
    include
)

include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories(${CUDA_INCLUDE_DIRS})


find_package(OpenCV REQUIRED)
find_package (Threads REQUIRED)
find_package(CUDA REQUIRED)

if(${CUDA_FOUND})
	set(CUDA_NVCC_FLAGS -arch=sm_61;-O3;-G;-g;-std=c++11)
	link_directories($ENV{CUDA_PATH}/lib/x64)
else(${CUDA_FOUND})
	MESSAGE(STATUS "cuda not found!")
endif(${CUDA_FOUND})

add_library(lib_core_cxx SHARED src/load_data.cpp
                                 	 src/im2col.c 
                                 	 src/list.c
                                 	 src/load_data_utils.c
                                 	 src/read_model.c 
									 src/parse_utils.c
									 src/convolution_layer.c
									 src/network.c
									 src/gemm.c
									 src/dense.c
									 src/global_avg.c
									 src/flatten.c
									 src/col2im.c)

cuda_add_library(lib_core_cu SHARED src/matrix_mul.cu
									src/im2col_gpu.cu
									src/gemm.cu
									src/matrix_mul_shared.cu)

ADD_EXECUTABLE(demo "test/main.c")

target_link_libraries(demo lib_core_cxx lib_core_cu ${OpenCV_LIBS} )
