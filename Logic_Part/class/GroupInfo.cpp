//
// Created by 孙璋亮 on 2019-08-30.
//

#include "GroupInfo.h"

// todo:
std::vector<UserInfo *> *GroupInfo::getUsers() {
    return Members;
}

// todo:
ChatInfo *GroupInfo::getChat() {
    return nullptr;
}

unsigned int GroupInfo::getGroupId() {
    return GroupId;
}

std::string GroupInfo::getNickName() {
    return NickName;
}

std::string GroupInfo::getAvatarPath() {
    return AvatorPath;
}

std::string GroupInfo::getNotice() {
    return Notice;
}

GroupInfo::GroupInfo() {
    chat = nullptr;
    Members = nullptr;
};

GroupInfo::~GroupInfo() {
    if (chat)
        delete chat;
    if (Members)
        delete Members;
}
