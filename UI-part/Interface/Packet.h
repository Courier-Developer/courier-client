//
// Created by ervinxie on 8/30/19.
//

#ifndef COURIER_CLIENT_PACKET_H
#define COURIER_CLIENT_PACKET_H

#include <vector>
#include "User.h"

class Packet {
    virtual std::vector<User *> &getUsers() = 0;

    virtual std::string getName() = 0;

    virtual int getPriority() = 0;//1:BlankList 2:Common 3:Favored
};

#endif //COURIER_CLIENT_PACKET_H
