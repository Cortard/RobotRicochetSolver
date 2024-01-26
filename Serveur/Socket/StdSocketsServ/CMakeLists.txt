cmake_minimum_required(VERSION 3.25)
project(RicochetSocketsServer)

set(CMAKE_CXX_STANDARD 17)

IF (WIN32)
    link_libraries(ws2_32 wsock32)
ENDIF()

SET("OpenCV_DIR" "/usr/share/OpenCV")
find_package( OpenCV REQUIRED )

MESSAGE(STATUS "Include dirs ${OpenCV_INCLUDE_DIRS}")
MESSAGE(STATUS "LINK LIBRARIES ${OpenCV_LIBS}")

add_executable(RicochetSocketServer.exe main.cpp
        Client/Client.cpp
        Client/Client.h
        Logs/Logs.cpp
        Logs/Logs.h
        Server/Server.cpp
        Server/Server.h
        socket.h
)

target_link_libraries(RicochetSocketServer.exe ${OpenCV_LIBS})