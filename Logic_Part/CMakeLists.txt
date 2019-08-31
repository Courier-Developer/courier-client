cmake_minimum_required(VERSION 3.14)
project(Logic_Part)

set(CMAKE_CXX_STANDARD 14)

INCLUDE_DIRECTORIES(../UI-part/Interface)

#AUX_SOURCE_DIRECTORY(Interface DIR_INT)

AUX_SOURCE_DIRECTORY(class DIR_CLS)

AUX_SOURCE_DIRECTORY(../UI-part/Interface DIR_INT)
add_executable(Logic_Part main.cpp ${DIR_CLS} class/DateTime.h)