cmake_minimum_required(VERSION 3.14)
project(Exam)

set(CMAKE_CXX_STANDARD 17)


add_executable(main main.cpp List/List.h  "HashTable/Hash.h" "HashTable/OpenAdressing.h" "HashTable/SeparateChaining.h" "Interface/Container.h")
target_include_directories(main PRIVATE ./)

