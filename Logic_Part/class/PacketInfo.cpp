//
// Created by 孙璋亮 on 2019-08-30.
//

#include "PacketInfo.h"


std::string PacketInfo::getName() {
    return std::string();
}

int PacketInfo::getPriority() {
    return 0;
}

std::vector<User *> &PacketInfo::getUsers() {
    return Members;
}
