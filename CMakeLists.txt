cmake_minimum_required(VERSION 3.13)
project(courier-client)
AUX_SOURCE_DIRECTORY(src DIR_SRCS)
set(CMAKE_CXX_STANDARD 17)

add_executable(courier-client ${DIR_SRCS})