cmake_minimum_required(VERSION 3.22.1 FATAL_ERROR)

if(USE_UDP)
    project(
            client-udp
            LANGUAGES CXX
    )

    add_executable(${PROJECT_NAME} client-udp.cpp)
    target_link_libraries(${PROJECT_NAME} PRIVATE sodium)
else ()
    project(
            client-tcp
            LANGUAGES CXX
    )

    add_executable(${PROJECT_NAME} client-tcp.cpp)
    target_link_libraries(${PROJECT_NAME} PRIVATE sodium)
endif ()
