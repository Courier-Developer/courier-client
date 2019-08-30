//
// Created by ervinxie on 8/30/19.
//

#ifndef COURIER_CLIENT_GROUP_H
#define COURIER_CLIENT_GROUP_H

#include <vector>
#include "User.h"
#include "Message.h"
#include "Chat.h"

class Group {
public:
    virtual std::vector<User *> &getUsers() = 0;

    virtual Chat *getChat() = 0;

    virtual unsigned int getGroupId() = 0;

    virtual std::string getNickName() = 0;

    virtual std::string getAvatarPath() = 0;

    virtual std::string getNotice() = 0;


};


#endif //COURIER_CLIENT_GROUP_H