cmake_minimum_required(VERSION 3.22.1 FATAL_ERROR)

project(
        client
        LANGUAGES CXX
)

add_executable(${PROJECT_NAME}-udp client-udp.cpp)
target_link_libraries(${PROJECT_NAME}-udp PRIVATE sodium)

add_executable(${PROJECT_NAME}-tcp client-tcp.cpp)
target_link_libraries(${PROJECT_NAME}-tcp PRIVATE sodium)

add_executable(${PROJECT_NAME}-udp-e client-udp-e.cpp)
target_link_libraries(${PROJECT_NAME}-udp-e PRIVATE sodium)

add_executable(${PROJECT_NAME}-tcp-e client-tcp-e.cpp)
target_link_libraries(${PROJECT_NAME}-tcp-e PRIVATE sodium)

