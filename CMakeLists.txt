cmake_minimum_required(VERSION 3.21)
project(Lab1)

set(CMAKE_CXX_STANDARD 14)

add_executable(Lab1 main.cpp src/setup.cpp headers/setup.h src/fill.cpp headers/fill.h src/utils.cpp headers/utils.h)
