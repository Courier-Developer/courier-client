cmake_minimum_required(VERSION 3.13)
project(courier-client)

set(CMAKE_CXX_STANDARD 17)


AUX_SOURCE_DIRECTORY(src DIR_SRCS)

AUX_SOURCE_DIRECTORY(include DIR_INC)

AUX_SOURCE_DIRECTORY(../UI-part/Interface DIR_INT)

ADD_EXECUTABLE(courier-client ${DIR_SRCS} ${DIR_INC} ${DIR_INT} ../UI-part/Interface/DateTime.h)

