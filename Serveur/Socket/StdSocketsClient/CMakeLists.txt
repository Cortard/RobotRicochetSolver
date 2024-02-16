cmake_minimum_required(VERSION 3.25)
project(StdSocketsClient)

set(CMAKE_CXX_STANDARD 17)

SET("OpenCV_DIR" "/usr/share/OpenCV")
find_package( OpenCV REQUIRED )

MESSAGE(STATUS "Include dirs ${OpenCV_INCLUDE_DIRS}")
MESSAGE(STATUS "LINK LIBRARIES ${OpenCV_LIBS}")

IF (WIN32)
    link_libraries(ws2_32 wsock32)
ENDIF()

add_executable(StdSocketsClient main.cpp
        configue.h
        sha256/sha256.h
        sha256/sha256.cpp
        ../RicochetSocketsServer/Socket/Socket.h
        ../RicochetSocketsServer/Socket/Socket.cpp
        ../RicochetSocketsServer/Logs/Logs.h
        ../RicochetSocketsServer/Logs/Logs.cpp
)

target_link_libraries(StdSocketsClient ${OpenCV_LIBS})