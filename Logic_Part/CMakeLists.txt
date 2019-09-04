cmake_minimum_required(VERSION 3.14)
project(Logic_Part)

set(CMAKE_CXX_STANDARD 17)


INCLUDE_DIRECTORIES(msgpack-c/include)
INCLUDE_DIRECTORIES(../UI-part/Interface)

INCLUDE_DIRECTORIES(include)
#AUX_SOURCE_DIRECTORY(Interface DIR_INT)

AUX_SOURCE_DIRECTORY(UI-Interface DIR_CLS)

#add_subdirectory(FeverRPC)

INCLUDE_DIRECTORIES(feverrpc/include)



add_executable(Logic_Part ${DIR_CLS} main.cpp Dealer.cpp Dealer.h feverrpc/src/feverrpc-client.cpp feverrpc/src/feverrpc.cpp)

#add_executable(Test main.cpp ${DIR_CLS})