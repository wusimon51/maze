cmake_minimum_required(VERSION 3.16)
project(maze)
set(CMAKE_CXX_STANDARD 17)

add_executable(maze main.cpp backtrack.cpp Cell.cpp Cell.h)
