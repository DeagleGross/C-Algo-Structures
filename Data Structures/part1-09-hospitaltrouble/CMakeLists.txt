cmake_minimum_required(VERSION 3.12)
project(part1_09_hospitaltrouble)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(part1_09_hospitaltrouble
        main.cpp
        parts.cpp
        parts.h)

add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)
