//
// Created by 孙璋亮 on 2019-08-30.
//

#ifndef COURIER_CLIENT_PACKETINFO_H
#define COURIER_CLIENT_PACKETINFO_H


#include <Packet.h>
#include "UserInfo.h"

//分组类
class PacketInfo: public Packet {

private:
    std::vector<unsigned int> MemberId;
    std::string PacketName;
    int PacketId;   //分组id
    std::vector<Userinfo *> Members;

public:
private:
    std::vector<User *> &getUsers() override;

public:
    std::string getName() override;

    int getPriority() override;

};


#endif //COURIER_CLIENT_PACKETINFO_H
