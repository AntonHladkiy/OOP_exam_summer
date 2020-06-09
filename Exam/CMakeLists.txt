cmake_minimum_required(VERSION 3.14)
project(Exam)

set(CMAKE_CXX_STANDARD 17)


option(BUILD_TESTS "Build tests" ON)

add_executable(main main.cpp)
target_include_directories(main PRIVATE ./)

if (BUILD_TESTS)
    add_executable(tests Tests/Test.cpp)
    target_include_directories(tests PRIVATE ./)
endif()
