cmake_minimum_required(VERSION 3.12)
project(Technopark_C_IZ1)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-g -O0 -Wall -Werror -Wpedantic -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "-lgcov --coverage")

add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(Technopark_C_IZ1 main.c timetable.c lesson.c)
add_executable(Technopark_C_IZ1_unittests test.cpp testing.c timetable.c lesson.c)

target_link_libraries(Technopark_C_IZ1_unittests gtest gtest_main)

enable_testing()

add_test(NAME lesson COMMAND test)