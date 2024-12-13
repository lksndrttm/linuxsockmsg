cmake_minimum_required(VERSION 3.20.0)

set(VERSION "0.0.1")
project(server VERSION ${VERSION} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(server 
    src/main.cpp
    include/thread_pool.h
    src/thread_pool.cpp
    include/logger.h
    src/logger.cpp
    include/server.h
    src/server.cpp
)

target_compile_options(server PRIVATE -Wall -Wextra -Wpedantic -Werror)
target_link_libraries(server PRIVATE connection)

target_include_directories(server PRIVATE include)

