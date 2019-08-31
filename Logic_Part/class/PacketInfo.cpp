//
// Created by 孙璋亮 on 2019-08-30.
//

#include "PacketInfo.h"


std::vector<User *> *PacketInfo::getUsers() {
    return nullptr;
}

std::string PacketInfo::getName() {
    return PacketName;
}

int PacketInfo::getPriority() {
    return PacketId;
}


const std::string &PacketInfo::getPacketName() const {
    return PacketName;
}

int PacketInfo::getPacketId() const {
    return PacketId;
}

std::vector<UserInfo *> *PacketInfo::getMembers() const {
    return Members;
}

PacketInfo::~PacketInfo() {
    if(Members)
        delete Members;
}

void PacketInfo::AddUser(UserInfo *user) {
    if (Members)
    {
        Members->push_back(user);
    }
    else
    {
        Members=new std::vector<UserInfo *>;
    }
}

PacketInfo::PacketInfo(const std::string &packetName, int packetId) : PacketName(packetName), PacketId(packetId) {}
