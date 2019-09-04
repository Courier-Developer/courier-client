cmake_minimum_required(VERSION 3.14)
project(courier-client)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
add_subdirectory(UI-part)

add_subdirectory(Logic_Part)

