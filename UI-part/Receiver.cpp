//
// Created by ervinxie on 9/2/19.
//

#include "View/implement.h"

Receiver::Receiver(std::vector<PacketInfo *> &plist,
                   std::vector<GroupInfo *> &glist,
                   std::vector<ChatInfo *> &clist,
                   UserInfo &me) :
        plist(plist),
        glist(glist),
        clist(clist),
        me(me) {}

void Receiver::debug() {
    std::cout << me.getNickName() << std::endl;
    for (auto p : plist) {
        std::cout << p->getName() << std::endl;
        for (auto u : *(p->getUsers())) {
            std::cout << u->getNickName() << std::endl;
        }
    }
    for (auto g : glist) {
        std::cout << g->getNickName() << std::endl;
        for (auto u : *(g->getUsers())) {
            std::cout << u->getNickName() << std::endl;
        }
    }
    for (auto c : clist) {
        std::cout << c->getTotype() << std::endl;
        if (c->getTotype() == 1) {
            std::cout << c->getToUser()->getNickName() << std::endl;
        } else {
            std::cout << c->getToGroup()->getNickName() << std::endl;
        }
        for (auto m : *(c->getMsgList())) {
            std::cout << m->getContent() << " " << m->getCreateTime().getString() << std::endl;
        }
    }

}
