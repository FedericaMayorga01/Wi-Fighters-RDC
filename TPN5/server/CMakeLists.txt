cmake_minimum_required(VERSION 3.22.1 FATAL_ERROR)

project(
        server
        LANGUAGES CXX
)

add_executable(${PROJECT_NAME} server.cpp)
