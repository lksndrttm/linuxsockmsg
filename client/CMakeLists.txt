cmake_minimum_required(VERSION 3.20.0)

set(VERSION "0.0.1")
project(client VERSION ${VERSION} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(client 
    src/main.cpp
    include/client.h
    src/client.cpp
)

target_compile_options(client PRIVATE -Wall -Wextra -Wpedantic -Werror)
target_link_libraries(client PRIVATE connection)

target_include_directories(client PRIVATE include)
