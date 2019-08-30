//
// Created by 孙璋亮 on 2019-08-30.
//

#include "UserInfo.h"

unsigned int UserInfo::getUserId() {
    return UserId;
}

std::string UserInfo::getUserName() {
    return UserName;
}

std::string UserInfo::getNickName() {
    return NickName;
}

std::string UserInfo::getAvatarPath() {
    return AvatorPath;
}

std::string UserInfo::getSignature() {
    return Signature;
}

// todo:
Chat *UserInfo::getChat() {
    return nullptr;
}


const std::string &UserInfo::getAvatorPath() const {
    return AvatorPath;
}

int UserInfo::getStatus() const {
    return Status;
}

void UserInfo::setUserId(unsigned int UserId) {
    UserInfo::UserId = UserId;
}

void UserInfo::setUserName(const std::string &UserName) {
    UserInfo::UserName = UserName;
}

void UserInfo::setNickName(const std::string &NickName) {
    UserInfo::NickName = NickName;
}

void UserInfo::setSignature(const std::string &Signature) {
    UserInfo::Signature = Signature;
}

void UserInfo::setAvatorPath(const std::string &AvatorPath) {
    UserInfo::AvatorPath = AvatorPath;
}

void UserInfo::setStatus(int status) {
    UserInfo::Status = status;
}

UserInfo::UserInfo() {}

UserInfo::~UserInfo() {
    if (InChat)
        delete InChat;
}

UserInfo::UserInfo(unsigned int UserId, const std::string &UserName, const std::string &NickName,
                   const std::string &Signature, const std::string &AvatorPath, int status, Chat *InChat,
                   Packet *InPacket, std::vector<Group *> *InGroups) : UserId(UserId), UserName(UserName),
                                                                       NickName(NickName), Signature(Signature),
                                                                       AvatorPath(AvatorPath), Status(status),
                                                                       InChat(InChat), InPacket(InPacket),
                                                                       InGroups(InGroups) {}

UserInfo::UserInfo(unsigned int UserId, const std::string &UserName, const std::string &NickName,
                   const std::string &Signature, const std::string &AvatorPath, int status) : UserId(UserId),
                                                                                              UserName(UserName),
                                                                                              NickName(NickName),
                                                                                              Signature(Signature),
                                                                                              AvatorPath(AvatorPath),
                                                                                              Status(status) {}

UserInfo::UserInfo(unsigned int UserId, const std::string &UserName, const std::string &NickName,
                   const std::string &Signature, const std::string &AvatorPath, int Status, int packet) : UserId(
        UserId), UserName(UserName), NickName(NickName), Signature(Signature), AvatorPath(AvatorPath), Status(Status),
                                                                                                          packet(packet) {}





