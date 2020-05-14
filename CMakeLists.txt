cmake_minimum_required(VERSION 3.2)

PROJECT(build_darknet)

INCLUDE_DIRECTORIES(
    include
)

AUX_SOURCE_DIRECTORY(
    . DIR_SRCS
)

 ADD_LIBRARY(lib_core SHARED src/list.c src/read_model.c)


ADD_EXECUTABLE(demo "test/main.c")

target_link_libraries(demo lib_core)
