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

void ChatInfo::AddMessage(MessageInfo *msg) {
    if (MessageList) {
        MessageList->push_back(msg);
    } else{
        MessageList=new std::vector<MessageInfo *>;
        MessageList->push_back(msg);
    }
    if (LastContent->getCreateTime() < msg->getCreateTime())
        LastContent=msg;
}

