PROJECT(core)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6) 

AUX_SOURCE_DIRECTORY(./assets/ assets_src_file)
file(GLOB assets_head_file ./assets/*.h)

AUX_SOURCE_DIRECTORY(./math/ math_src_file)
file(GLOB math_head_file ./math/*.h)


AUX_SOURCE_DIRECTORY(. src_file)
file(GLOB head_file ./*.h)

set(SRC_FILE
    ${assets_src_file}
    ${math_src_file}
    ${src_file}
)

set(HEAD_FILE
    ${assets_head_file}
    ${math_head_file}
    ${head_file}
)

ADD_LIBRARY(core ${SRC_FILE} ${HEAD_FILE})