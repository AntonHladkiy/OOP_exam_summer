cmake_minimum_required(VERSION 3.14)
project(Exam)

set(CMAKE_CXX_STANDARD 17)


add_executable(main main.cpp AVLTree/AVLTree.cpp)
target_include_directories(main PRIVATE ./)

