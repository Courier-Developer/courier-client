//
// Created by 孙璋亮 on 2019-08-30.
//

#include "ChatInfo.h"

//todo:
std::vector<MessageInfo *> *ChatInfo::getMsgList() {
    return nullptr;
}
//todo
int ChatInfo::getChatWith() {
    return 0;
}
//todo
UserInfo *ChatInfo::getUser() {
    return nullptr;
}
//todo
GroupInfo *ChatInfo::getGroup() {
    return nullptr;
}

ChatInfo::~ChatInfo() {
    if (MessageList)
        delete MessageList;
}

