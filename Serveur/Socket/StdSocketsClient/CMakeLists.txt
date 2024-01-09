cmake_minimum_required(VERSION 3.25)
project(StdSocketsClient)

set(CMAKE_CXX_STANDARD 17)

IF (WIN32)
    link_libraries(ws2_32 wsock32)
ENDIF()

add_executable(StdSocketsClient main.cpp
        configue.h
)
