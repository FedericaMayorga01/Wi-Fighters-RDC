cmake_minimum_required(VERSION 3.22.1 FATAL_ERROR)

project(
        server
        LANGUAGES CXX
)

add_executable(${PROJECT_NAME}-udp server-udp.cpp)
target_link_libraries(${PROJECT_NAME}-udp PRIVATE sodium)

add_executable(${PROJECT_NAME}-tcp server-tcp.cpp)
target_link_libraries(${PROJECT_NAME}-tcp PRIVATE sodium)

add_executable(${PROJECT_NAME}-udp-e server-udp-e.cpp)
target_link_libraries(${PROJECT_NAME}-udp-e PRIVATE sodium)

add_executable(${PROJECT_NAME}-tcp-e server-tcp-e.cpp)
target_link_libraries(${PROJECT_NAME}-tcp-e PRIVATE sodium)


