cmake_minimum_required(VERSION 3.27)
project(sockets)

set(CMAKE_CXX_STANDARD 23)

add_executable(sockets main.cpp
        broadcaster.cpp
        broadcaster.h
        server.cpp
        server.h
)

# Link against the Winsock library
target_link_libraries(sockets wsock32 ws2_32)