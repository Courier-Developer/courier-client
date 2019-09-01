cmake_minimum_required(VERSION 3.14)
project(Logic_Part)

set(CMAKE_CXX_STANDARD 14)

INCLUDE_DIRECTORIES(../UI-part/Interface)

#AUX_SOURCE_DIRECTORY(Interface DIR_INT)

AUX_SOURCE_DIRECTORY(UI-Interface DIR_CLS)

#add_subdirectory(FeverRPC)

add_executable(Logic_Part ${DIR_CLS} main.cpp Dealer.cpp Dealer.h)

#add_executable(Test main.cpp ${DIR_CLS})