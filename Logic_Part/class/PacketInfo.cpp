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

const std::vector<unsigned int> &PacketInfo::getMemberId() const {
    return MemberId;
}

PacketInfo::PacketInfo(const std::vector<unsigned int> &memberId, const std::string &packetName, int packetId)
        : MemberId(memberId), PacketName(packetName), PacketId(packetId) {}

const std::string &PacketInfo::getPacketName() const {
    return PacketName;
}

int PacketInfo::getPacketId() const {
    return PacketId;
}

std::vector<UserInfo *> *PacketInfo::getMembers() const {
    return Members;
}
