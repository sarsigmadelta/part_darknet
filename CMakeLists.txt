cmake_minimum_required(VERSION 3.2)

PROJECT(build_darknet)

set( CMAKE_C_FLAGS "-pthread" )

INCLUDE_DIRECTORIES(
    include
)

AUX_SOURCE_DIRECTORY(
    . DIR_SRCS
)

ADD_LIBRARY(lib_core SHARED src/list.c src/read_model.c src/load_data.cpp src/load_data_utils.c)

find_package(OpenCV REQUIRED)
find_package (Threads REQUIRED)

include_directories( ${OpenCV_INCLUDE_DIRS} )


ADD_EXECUTABLE(demo "test/main.c")

target_link_libraries(demo lib_core ${OpenCV_LIBS})
