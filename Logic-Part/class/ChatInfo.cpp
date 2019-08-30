//
// Created by 孙璋亮 on 2019-08-30.
//

#include "ChatInfo.h"

//todo:
std::vector<Message *> &ChatInfo::getMsgList() {
    return <#initializer#>;
}
//todo
int ChatInfo::getChatWith() {
    return 0;
}
//todo
User *ChatInfo::getUser() {
    return nullptr;
}
//todo
Group *ChatInfo::getGroup() {
    return nullptr;
}

ChatInfo::ChatInfo(std::vector<Message *> *MessageList = nullptr, User *ToUser= nullptr, Group *ToGroup=nullptr) : MessageList(MessageList),
                                                                                        ToUser(ToUser),
                                                                                        ToGroup(ToGroup) {}
