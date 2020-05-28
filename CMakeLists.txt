cmake_minimum_required(VERSION 3.2)

PROJECT(build_darknet)

set(CMAKE_C_FLAGS "-pthread")
set(CMAKE_CXX_FLAGS "-fPIC" )

INCLUDE_DIRECTORIES(
    include
)

include_directories(${CUDA_INCLUDE_DIRS})

#AUX_SOURCE_DIRECTORY(
#    . DIR_SRCS
#)

find_package(OpenCV REQUIRED)
find_package (Threads REQUIRED)
find_package(CUDA REQUIRED)
if(${CUDA_FOUND})
	set(CUDA_SOURCE_PROPERTY_FORMAT OBJ)
	set(CUDA_SEPARABLE_COMPILATION ON)
	include_directories(${CUDA_INCLUDE_DIRS})
	set(CUDA_PROPAGATE_HOST_FLAGS OFF)
	set(CUDA_NVCC_FLAGS -arch=sm_61;-O3;-G;-g;-std=c++11)
	#SET(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS};-gencode arch=compute_61,code=sm_61;-std=c++11;-O3;-G;-g)
	link_directories($ENV{CUDA_PATH}/lib/x64)
else(${CUDA_FOUND})
	MESSAGE(STATUS "cuda not found!")
endif(${CUDA_FOUND})

include_directories( ${OpenCV_INCLUDE_DIRS} )


cuda_add_library(lib_core SHARED src/load_data.cpp
                                 src/im2col.c 
                                 src/list.c
                                 src/load_data_utils.c
                                 src/read_model.c
                                 src/matrix_mul.cu)

ADD_EXECUTABLE(demo "test/main.c")

target_link_libraries(demo lib_core ${OpenCV_LIBS})
