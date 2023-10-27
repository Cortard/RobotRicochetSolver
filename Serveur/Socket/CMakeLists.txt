cmake_minimum_required(VERSION 3.26)
project(Socket)

set(CMAKE_CXX_STANDARD 14)

include_directories(StdSockets-Jaillet)

add_executable(Socket
        StdSockets-Jaillet/Client/client.cpp
        StdSockets-Jaillet/ClientAsync/clientAsync.cpp
        StdSockets-Jaillet/Server/server.cpp
        StdSockets-Jaillet/ServerAsync/serverAsync.cpp
        StdSockets-Jaillet/socket.cpp
        StdSockets-Jaillet/socket.h
        StdSockets-Jaillet/talk.cpp
        StdSockets-Jaillet/talk.h)
