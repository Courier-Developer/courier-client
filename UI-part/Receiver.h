//
// Created by ervinxie on 9/2/19.
//

#ifndef COURIER_CLIENT_RECEIVER_H
#define COURIER_CLIENT_RECEIVER_H

#include "View/ThemeManage.h"

class Receiver {
public:
    Receiver(std::vector<PacketInfo *> &plist,
             std::vector<GroupInfo *> &glist,
             std::vector<ChatInfo *> &clist,
             UserInfo *me);

    std::vector<PacketInfo *> &plist;
    std::vector<GroupInfo *> &glist;
    std::vector<ChatInfo *> &clist;
    UserInfo *me;

    MainWindow *mainWindow;

    Glib::Dispatcher dispatcher;

    void debug();

    void friendRequest(UserInfo *);

    void friendDelete(UserInfo *);

    void friendUpdate(UserInfo *);


    void groupRequest(GroupInfo *);

    void groupUpdate(GroupInfo *);

    void groupDelete(GroupInfo*);

    void receiveMessage(MessageInfo *msg);
};


#endif //COURIER_CLIENT_RECEIVER_H
