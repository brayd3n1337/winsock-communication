cmake_minimum_required(VERSION 3.27)
project(clientsocket)

set(CMAKE_CXX_STANDARD 17)

add_executable(clientsocket main.cpp
        client.cpp
        client.h
        broadcaster.cpp
        broadcaster.h
)
target_link_libraries(clientsocket wsock32 ws2_32)