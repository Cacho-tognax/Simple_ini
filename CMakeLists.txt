cmake_minimum_required(VERSION 3.3)
project(Simple_ini)

add_subdirectory(unittest-cpp-master)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Ini_manager.cpp Ini_manager.h Ini_section.cpp Ini_section.h Ini_entry.h Ini_entry.cpp Invalid_entry_exception.h)
add_executable(Simple_ini ${SOURCE_FILES})