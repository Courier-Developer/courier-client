//
// Created by ervinxie on 8/30/19.
//

#ifndef COURIER_CLIENT_PACKET_H
#define COURIER_CLIENT_PACKET_H

#include <vector>
#include "User.h"

class Packet {
    std::vector<User *> users;

    virtual std::string getName() = 0;

    virtual int getPriority() = 0;
};

#endif //COURIER_CLIENT_PACKET_H
