cmake_minimum_required(VERSION 3.26)
project(StdSocketsServer)

set(CMAKE_CXX_STANDARD 17)

IF (WIN32)
    link_libraries(ws2_32 wsock32)
ENDIF()

add_executable(StdSockets main.cpp
        logs/Logs.cpp
        logs/Logs.h
        devMode.h
        clients/Client.cpp
        clients/Client.h
)

