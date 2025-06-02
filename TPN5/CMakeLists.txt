cmake_minimum_required(VERSION 3.22.1 FATAL_ERROR)
project(na)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SODIUM REQUIRED libsodium)
include_directories(${SODIUM_INCLUDE_DIRS})
link_directories(${SODIUM_LIBRARY_DIRS})

option(IS_SERVER 1)
option(USE_UDP 0)

if(IS_SERVER)
    add_subdirectory(server)
else()
    add_subdirectory(client)
endif ()
