cmake_minimum_required(VERSION 3.15)
project(IZ1 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-g -O0 -Wall -Werror -Wpedantic -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "-lgcov --coverage")
set(LIB_SOURCE_FILE testing.h testing.c)

add_library(_all_headers STATIC ${LIB_SOURCE_FILE})

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(tests test.cpp)
add_executable(IZ1 main.c lesson.c lesson.h)

target_link_libraries(tests ${GTEST_LIBRARIES} gtest_main pthread)
target_link_libraries(tests _all_headers)
target_link_libraries(IZ1 _all_headers)
target_link_libraries(tests -fprofile-arcs)

enable_testing()

add_test(NAME tests COMMAND tests)