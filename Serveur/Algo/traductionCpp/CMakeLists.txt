cmake_minimum_required(VERSION 3.26)
project(traductionCpp)

set(CMAKE_CXX_STANDARD 17)

add_executable(traductionCpp main.cpp
                             Game.h
                             Solver.h
                             Solver.cpp
        solver.cpp)
