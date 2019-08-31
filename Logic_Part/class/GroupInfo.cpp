//
// Created by 孙璋亮 on 2019-08-30.
//

#include "GroupInfo.h"
extern std::vector<ChatInfo *> AllChat;


// todo:
std::vector<UserInfo *> *GroupInfo::getUsers() {
    return Members;
}

// todo:
ChatInfo *GroupInfo::getChat() {
    if (chat)
        return chat;
    else{
        chat=new ChatInfo;
        chat->setTotype(2);
        chat->setToGroup(this);
//        AddChat(chat);
        AllChat.push_back(chat);
        return chat;
    }
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

const std::vector<unsigned int> &GroupInfo::getMemberId() const {
    return MemberId;
}

void GroupInfo::AddUser(UserInfo *user) {
    if (Members) {
        Members->push_back(user);
    } else {
        Members = new std::vector<UserInfo *>;
        Members->push_back(user);
    }
}

GroupInfo::GroupInfo(unsigned int groupId, const std::string &nickName, const std::string &avatorPath,
                     const std::string &notice, const std::vector<unsigned int> &memberId) : GroupId(groupId),
                                                                                             NickName(nickName),
                                                                                             AvatorPath(avatorPath),
                                                                                             Notice(notice),
                                                                                             MemberId(memberId) {}
