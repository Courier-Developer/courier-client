//
// Created by ervinxie on 8/30/19.
//

#ifndef COURIER_CLIENT_CHAT_H
#define COURIER_CLIENT_CHAT_H

#include <vector>
#include "Declare.h"

class Chat {
    virtual std::vector<Message *>& getMsgList() = 0;

    virtual int getChatWith() = 0;// 1:Single Chat 2:GroupChat

    virtual User *getUser() = 0;

    virtual Group *getGroup() = 0;

};


#endif //COURIER_CLIENT_CHAT_H
