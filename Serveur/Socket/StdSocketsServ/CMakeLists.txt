cmake_minimum_required(VERSION 3.25)
project(StdSocketsServer)

set(CMAKE_CXX_STANDARD 17)

IF (WIN32)
    link_libraries(ws2_32 wsock32)
ENDIF()

SET("OpenCV_DIR" "/usr/share/OpenCV")
find_package( OpenCV REQUIRED )

MESSAGE(STATUS "Include dirs ${OpenCV_INCLUDE_DIRS}")
MESSAGE(STATUS "LINK LIBRARIES ${OpenCV_LIBS}")

add_executable(RicochetSocketServer.exe main.cpp
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
        boardBuilder/boardBuilder.cpp
        boardIsolation/boardIsolation.h
        boardIsolation/boardIsolation.cpp
        jpegBuilder/jpegBuilder.h
        jpegBuilder/jpegBuilder.cpp
        boardBuilder/board.h
)

target_link_libraries(RicochetSocketServer.exe ${OpenCV_LIBS})