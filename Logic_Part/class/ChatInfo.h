//
// Created by 孙璋亮 on 2019-08-30.
//

#ifndef COURIER_CLIENT_CHATINFO_H
#define COURIER_CLIENT_CHATINFO_H

#include <Chat.h>
#include "UserInfo.h"

class ChatInfo : public Chat {

private:
    std::vector<MessageInfo *> *MessageList;
    UserInfo *ToUser;
    GroupInfo *ToGroup;
    int UnreadNumbers; //未读消息数量
public:
    std::vector<Message *> *getMsgList() override;

    int getChatWith() override; //1.个人 2.群

    User *getUser() override;

    Group *getGroup() override;

    ~ChatInfo();
};


#endif //COURIER_CLIENT_CHATINFO_H
