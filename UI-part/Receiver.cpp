//
// Created by ervinxie on 9/2/19.
//

#include "Receiver.h"

Receiver::Receiver(std::vector<PacketInfo *> &plist,
                   std::vector<GroupInfo *> &glist,
                   std::vector<ChatInfo *> &clist,
                   UserInfo *me) :
        plist(plist),
        glist(glist),
        clist(clist),
        me(me) {

}
