//
// Created by ervinxie on 9/2/19.
//

#ifndef COURIER_CLIENT_RECEIVER_H
#define COURIER_CLIENT_RECEIVER_H

#include "View/SignUp.h"

class Receiver {
public:
    Receiver(std::vector<PacketInfo *> &plist,
             std::vector<GroupInfo *> &glist,
             std::vector<ChatInfo *> &clist,
             UserInfo &me);

    std::vector<PacketInfo *> &plist;
    std::vector<GroupInfo *> &glist;
    std::vector<ChatInfo *> &clist;
    UserInfo &me;
    void debug();
};


#endif //COURIER_CLIENT_RECEIVER_H