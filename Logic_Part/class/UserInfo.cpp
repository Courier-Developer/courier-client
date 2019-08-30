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
    return InChat;
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



