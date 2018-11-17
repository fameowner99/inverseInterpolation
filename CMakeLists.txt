cmake_minimum_required(VERSION 3.12)
project(inverseInterpolation)

set(CMAKE_CXX_STANDARD 14)

find_library(libsdl SDL2)

add_executable(inverseInterpolation
        lab4.cpp)

target_link_libraries(inverseInterpolation ${libsdl})