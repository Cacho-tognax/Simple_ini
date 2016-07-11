cmake_minimum_required(VERSION 3.3)
find_package(UnitTest++ REQUIRED)

add_subdirectory(unittest-cpp-master)
set(unit_test_SOURCE_DIR, ./unittest-cpp-master)
include_directories(${unit_test_SOURCE_DIR}/include ${unit_test_SOURCE_DIR})

set(TEST_SOURCE_FILES runAllTests.cpp.cpp)
add_executable(run_simple_ini ${TEST_SOURCE_FILES})
target_link_libraries(run_simple_ini  TestUnitTest++ UnitTest++)