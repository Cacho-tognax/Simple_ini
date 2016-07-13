cmake_minimum_required(VERSION 3.5)

add_subdirectory(./googletest-master)
set(gtest_SOURCE_DIR, ./googletest-master)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


set(TEST_SOURCE_FILES runAllTests.cpp.cpp Ini_entry_test.cpp Ini_section_test.cpp)
add_executable(run_simple_ini ${TEST_SOURCE_FILES})
target_link_libraries(run_simple_ini gtest gtest_main core)