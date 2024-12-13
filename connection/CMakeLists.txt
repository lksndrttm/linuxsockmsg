cmake_minimum_required(VERSION 3.20.0)

set(VERSION "0.0.1")
project(connection VERSION ${VERSION} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(connection STATIC 
    include/connection.h
    src/connection.cpp
    include/connection_manager.h
    src/connection_manager.cpp
    include/exceptions.h
)

target_compile_options(connection PRIVATE -Wall -Wextra -Wpedantic -Werror)

target_include_directories(connection PUBLIC include)
