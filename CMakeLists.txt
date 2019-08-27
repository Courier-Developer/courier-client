cmake_minimum_required(VERSION 3.13)
project(courier-client)

set(CMAKE_CXX_STANDARD 17)

set(DIR_LIB include)

INCLUDE_DIRECTORIES(${DIR_LIB})

AUX_SOURCE_DIRECTORY(src DIR_SRCS)

ADD_EXECUTABLE(courier-client ${DIR_SRCS})

