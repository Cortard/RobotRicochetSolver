cmake_minimum_required(VERSION 3.26)
project(StdSocketsServer)

set(CMAKE_CXX_STANDARD 17)

link_libraries(ws2_32 wsock32)

add_executable(StdSockets main.cpp
)
