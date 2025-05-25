cmake_minimum_required(VERSION 3.22.1 FATAL_ERROR)
project(useless)

option(IS_SERVER 1)
option(USE_UDP 0)

if(IS_SERVER)
    add_subdirectory(server)
else()
    add_subdirectory(client)
endif ()
