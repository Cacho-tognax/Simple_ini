cmake_minimum_required(VERSION 3.3)
project(Simple_ini)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp main.cpp)
add_executable(Simple_ini ${SOURCE_FILES})