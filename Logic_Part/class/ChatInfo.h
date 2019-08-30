//
// Created by 孙璋亮 on 2019-08-30.
//

#ifndef COURIER_CLIENT_CHATINFO_H
#define COURIER_CLIENT_CHATINFO_H

#include <Chat.h>

class ChatInfo: public Chat {

private:
    std::vector<Message *> *MessageList;
    User *ToUser;
    Group *ToGroup;
    int UnreadNumbers;
public:


public:
    std::vector<Message *> &getMsgList() override;

    int getChatWith() override; //1.个人 2.群

    User *getUser() override;

    Group *getGroup() override;

};


#endif //COURIER_CLIENT_CHATINFO_H
