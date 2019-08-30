//
// Created by 孙璋亮 on 2019-08-30.
//

#include "GroupInfo.h"

// todo:
std::vector<User *> &GroupInfo::getUsers() {
    return <#initializer#>;
}

// todo:
Chat *GroupInfo::getChat() {
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

GroupInfo::GroupInfo(unsigned int GroupId, const std::string &NickName, const std::string &AvatorPath,
                     const std::string &Notice, const std::vector<unsigned int> &MemberId, Chat *chat = nullptr,
                     std::vector<User *> *Members = nullptr) : GroupId(GroupId), NickName(NickName),
                                                               AvatorPath(AvatorPath),
                                                               Notice(Notice), MemberId(MemberId), chat(chat),
                                                               Members(Members) {}
