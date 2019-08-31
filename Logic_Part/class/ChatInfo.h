//
// Created by 孙璋亮 on 2019-08-30.
//

#ifndef COURIER_CLIENT_CHATINFO_H
#define COURIER_CLIENT_CHATINFO_H

#include "predeclare.h"
#include "MessageInfo.h"

class ChatInfo{

private:
    std::vector<MessageInfo *> *MessageList;
    UserInfo *ToUser;
    GroupInfo *ToGroup;
    int UnreadNumbers; //未读消息数量
    MessageInfo *LastContent;
public:
    std::vector<MessageInfo *> *getMsgList();

    int getChatWith(); //1.个人 2.群

    UserInfo *getUser();

    GroupInfo *getGroup();

    ~ChatInfo();

    void AddMessage(MessageInfo * msg);
};


#endif //COURIER_CLIENT_CHATINFO_H
