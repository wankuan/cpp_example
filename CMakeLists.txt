cmake_minimum_required(VERSION 3.16)
project(demo1)
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(CMAKE_CXX_FLAGS "-g")
set(CMAKE_CXX_STANDARD 11)

add_executable(demo1 ConsoleApplication2.cpp)