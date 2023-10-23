cmake_minimum_required(VERSION 3.26)
project(traductionCpp)

set(CMAKE_CXX_STANDARD 17)

add_executable(traductionCpp main.cpp
        Game.h
        Entry.h
        Set.h
        solver.h
        solver.cpp
        solver.cpp)
