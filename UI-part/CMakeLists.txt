

# Use the package PkgConfig to detect GTK+ headers/library files
FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTKmm REQUIRED gtkmm-3.0)
INCLUDE_DIRECTORIES(../Logic_Part/msgpack-c/include)

INCLUDE_DIRECTORIES(../Logic_Part/feverrpc/include)
INCLUDE_DIRECTORIES(../Logic_Part/include)

INCLUDE_DIRECTORIES(${GTKmm_INCLUDE_DIRS})
LINK_DIRECTORIES(${GTKmm_LIBRARY_DIRS})
AUX_SOURCE_DIRECTORY(../Logic_Part/UI-Interface DIR_CLS)

add_executable(main main.cpp

        ${DIR_CLS}


        ../Logic_Part/Dealer.h
        ../Logic_Part/Dealer.cpp

        View/LogIn.cpp
        View/LogIn.h
        View/MainWindow.cpp
        View/MainWindow.h
        View/ChatWindow/ChatWindow.cpp
        View/ChatWindow/ChatWindow.h
        View/ContactWindow/ContactInfo.cpp
        View/ContactWindow/ContactInfo.h
        View/ChatWindow/ChatList.cpp
        View/ChatWindow/ChatList.h
        View/ChatWindow/Chatting.cpp
        View/ChatWindow/Chatting.h
        View/ContactWindow/ContactWindow.cpp
        View/ContactWindow/ContactWindow.h
        View/OtherWindow/OtherWindow.cpp
        View/OtherWindow/OtherWindow.h
        View/ContactWindow/ContactList.cpp
        View/ContactWindow/ContactList.h

        View/SignUp.cpp
        View/SignUp.h
        View/ContactWindow/GroupContactInfo.cpp
        View/ContactWindow/GroupContactInfo.h
        View/predeclare.h
        View/implement.h

        Receiver.cpp
        Receiver.h
        View/ChatWindow/HistroyMessage.cpp
        View/ChatWindow/HistroyMessage.h
        View/res/PixMan.cpp
        View/res/PixMan.h
        View/ChatWindow/ShowMessage.cpp
        View/ChatWindow/ShowMessage.h
        View/ContactWindow/PacketContactInfo.cpp
        View/ContactWindow/PacketContactInfo.h
        View/ThemeManage.cpp
        View/ThemeManage.h

        ../Logic_Part/include/src/feverrpc-client.cpp
        ../Logic_Part/include/src/feverrpc.cpp
        ../Logic_Part/include/Convert.cpp
        ../Logic_Part/file/MyFile.cpp
        )


TARGET_LINK_LIBRARIES(main ${GTKmm_LIBRARIES})

