//
// Created by 孙璋亮 on 2019-08-30.
//

#ifndef COURIER_CLIENT_GROUPINFO_H
#define COURIER_CLIENT_GROUPINFO_H


#include "UserInfo.h"
#include <string>
#include <vector>

class GroupInfo  {
private:
    unsigned int GroupId;
    std::string NickName;
    std::string AvatorPath;
    std::string Notice;
    std::vector<unsigned int> MemberId;
    ChatInfo *chat = nullptr;
    std::vector<UserInfo *> *Members = nullptr;
public:
    std::vector<UserInfo *> *getUsers();

    ChatInfo *getChat();

    virtual ~GroupInfo();

    GroupInfo();

    unsigned int getGroupId();

    std::string getNickName();

    std::string getAvatarPath();

    std::string getNotice();
};


#endif //COURIER_CLIENT_GROUPINFO_H
