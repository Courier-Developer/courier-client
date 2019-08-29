cmake_minimum_required(VERSION 3.13)
project(courier-client)

set(CMAKE_CXX_STANDARD 17)

set(DIR_LIB include)

INCLUDE_DIRECTORIES(${DIR_LIB})

AUX_SOURCE_DIRECTORY(src DIR_SRCS)

ADD_EXECUTABLE(courier-client ${DIR_SRCS} src/main.cpp include/Date.cpp include/Date.h src/Macro_Definition.h include/user_info.cpp include/user_info.h include/message_info.cpp include/message_info.h include/packet.cpp include/packet.h src/user_handle.cpp src/user_handle.h src/link_to_server.cpp src/link_to_server.h)

