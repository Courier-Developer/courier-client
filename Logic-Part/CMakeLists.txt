cmake_minimum_required(VERSION 3.13)
project(courier-client)

set(CMAKE_CXX_STANDARD 17)

INCLUDE_DIRECTORIES(../UI-part/Interface)

AUX_SOURCE_DIRECTORY(src DIR_SRCS)

AUX_SOURCE_DIRECTORY(include DIR_INC)

AUX_SOURCE_DIRECTORY(../UI-part/Interface DIR_INT)

ADD_EXECUTABLE(courier-client ${DIR_SRCS} ${DIR_INC} ${DIR_INT} ../UI-part/Interface/DateTime.h ../UI-part/Interface/DateTime.h class/UserInfo.cpp class/UserInfo.h class/ChatInfo.cpp class/ChatInfo.h class/GroupInfo.cpp class/GroupInfo.h class/PacketInfo.cpp class/PacketInfo.h src/UI_Part.cpp src/UI_Part.h src/Logic_Part.cpp src/Logic_Part.h)

