PROJECT(render)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6) 

set(GL_INCLUDE_PATH ${PROJECT_SOURCE_DIR}//..//thridpart//opengl CACHE PATH "opengl include path")
INCLUDE_DIRECTORIES(${GL_INCLUDE_PATH})

AUX_SOURCE_DIRECTORY(. src_file)

file(GLOB head_file ./*.h)

ADD_LIBRARY(render ${src_file} ${head_file})