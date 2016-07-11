cmake_minimum_required(VERSION 3.3)

add_subdirectory(unittest-cpp-master)

set(unit_test_SOURCE_DIR, ./unittest-cpp-master)
include_directories(${unit_test_SOURCE_DIR}/include ${unit_test_SOURCE_DIR})