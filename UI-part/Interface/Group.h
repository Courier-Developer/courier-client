//
// Created by ervinxie on 8/30/19.
//

#ifndef COURIER_CLIENT_GROUP_H
#define COURIER_CLIENT_GROUP_H

#include <vector>
#include "User.h"
#include "Message.h"
class Group {
public:
    std::vector<User *> users;

    virtual unsigned int getGroupId() = 0;

    virtual std::string getNickName() = 0;

    virtual std::string getAvatarPath() = 0;

    virtual std::string getNotice() = 0;

    std::vector<Message*> msgList;


};


#endif //COURIER_CLIENT_GROUP_H