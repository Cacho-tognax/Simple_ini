cmake_minimum_required(VERSION 3.3)

project(Simple_ini)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(Tests)

set(SOURCE_FILES main.cpp Ini_manager.cpp Ini_manager.h Ini_section.cpp Ini_section.h Ini_entry.h Ini_entry.cpp Invalid_entry_exception.h)
add_executable(Simple_ini main.cpp)
add_library(core ${SOURCE_FILES})
target_link_libraries(Simple_ini core)