cmake_minimum_required(VERSION 3.16.3)

project(popen_test)

set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
set (CMAKE_C_COMPILER "clang")
set (CMAKE_CXX_COMPILER "clang++")
set (CMAKE_VERBOSE_MAKEFILE ON)

set (SOURCES
    src/piple.cpp
    src/main.cpp
)

add_executable( ${PROJECT_NAME}
    ${SOURCES}
)

target_include_directories( ${PROJECT_NAME}
    PUBLIC
        ${WX_INCLUDE_DIR}
        ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries( ${PROJECT_NAME}
# if using llvm c++ lib, should do 
    c++
    c++abi
# if using self defined logs added this dynamic link library
    simplelogs
)
