cmake_minimum_required(VERSION 3.22.1 FATAL_ERROR)

if(USE_UDP)
    project(
            server-udp
            LANGUAGES CXX
    )

    add_executable(${PROJECT_NAME} server-udp.cpp)
else()
    project(
            server-tcp
            LANGUAGES CXX
    )

    add_executable(${PROJECT_NAME} server-tcp.cpp)
endif()