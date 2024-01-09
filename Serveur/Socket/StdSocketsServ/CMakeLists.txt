cmake_minimum_required(VERSION 3.25)
project(StdSocketsServer)

set(CMAKE_CXX_STANDARD 17)

IF (WIN32)
    link_libraries(ws2_32 wsock32)
ENDIF()

add_executable(StdSockets main.cpp
        logs/Logs.cpp
        logs/Logs.h
        clients/Client.cpp
        clients/Client.h
        configue.h
        Serveur.cpp
        Serveur.h
        solver/Solver.cpp
        solver/Solver.h
        solver/Game.h
        boardBuilder/boardBuilder.h
        boardIsolation/boardIsolation.h
        jpegBuilder/jpegBuilder.h
)

