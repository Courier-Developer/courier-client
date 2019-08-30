cmake_minimum_required(VERSION 3.13)
project(courier-client)

set(CMAKE_CXX_STANDARD 17)

set(DIR_LIB include)

INCLUDE_DIRECTORIES(${DIR_LIB})

AUX_SOURCE_DIRECTORY(src DIR_SRCS)

ADD_EXECUTABLE(courier-client ${DIR_SRCS} src/main.cpp src/MacroDefinition.h include/user_info.cpp include/user_info.h include/message_info.cpp include/message_info.h src/UserHandle.cpp src/UserHandle.h src/LinkToServer.cpp src/LinkToServer.h src/ChatHandle.cpp src/ChatHandle.h Interface/UserInfo.cpp Interface/UserInfo.h)

