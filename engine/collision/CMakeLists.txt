PROJECT(collision)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6) 

AUX_SOURCE_DIRECTORY(. src_file)

file(GLOB head_file ./*.h)

ADD_LIBRARY(collision ${src_file} ${head_file})