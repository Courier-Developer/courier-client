//
// Created by 孙璋亮 on 2019-08-31.
//

#ifndef COURIER_CLIENT_GLOBALVAR_H
#define COURIER_CLIENT_GLOBALVAR_H

#endif //COURIER_CLIENT_GLOBALVAR_H

#include <map>
#include <string>
#include <vector>
#include "UserInfo.h"
#include "GroupInfo.h"
#include "MessageInfo.h"
#include "PacketInfo.h"
#include "ChatInfo.h"

std::map<unsigned int, UserInfo *> AllUser;
std::vector<PacketInfo *> AllPacket;
std::vector<GroupInfo *> AllGroup;
std::map<int, PacketInfo *> PacketMap;
std::map<int, GroupInfo *> GroupMap;
UserInfo MyProfile;
UserInfo ChatTo;

UserInfo getMyInfo() {
    return MyProfile;
}

std::vector<PacketInfo *> &getAllPacket() {
    return AllPacket;
}

std::vector<GroupInfo *> &getAllGroup() {
    return AllGroup;
}
