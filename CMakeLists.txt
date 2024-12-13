cmake_minimum_required(VERSION 3.5.0)

set(VERSION "0.0.1")
project(socket VERSION ${VERSION} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(connection)
add_subdirectory(client)
add_subdirectory(server)
