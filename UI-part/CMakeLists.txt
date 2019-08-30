

# Use the package PkgConfig to detect GTK+ headers/library files
FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTKmm REQUIRED gtkmm-3.0)

INCLUDE_DIRECTORIES(${GTKmm_INCLUDE_DIRS})
LINK_DIRECTORIES(${GTKmm_LIBRARY_DIRS})

add_executable(main main.cpp Interface/User.h Interface/Message.h View/LogIn.cpp View/LogIn.h View/MainWindow.cpp View/MainWindow.h View/ChatWindow/ChatWindow.cpp View/ChatWindow/ChatWindow.h View/ContactWindow/ContactInfo.cpp View/ContactWindow/ContactInfo.h View/ChatWindow/ChatList.cpp View/ChatWindow/ChatList.h View/ChatWindow/Chatting.cpp View/ChatWindow/Chatting.h View/ContactWindow/ContactWindow.cpp View/ContactWindow/ContactWindow.h View/OtherWindow/OtherWindow.cpp View/OtherWindow/OtherWindow.h Interface/Group.h Interface/Packet.h Interface/Chat.h Interface/DateTime.h Interface/ChatEntity.h)

add_executable(test test.cpp)
TARGET_LINK_LIBRARIES(main ${GTKmm_LIBRARIES})

