//
// Created by 孙璋亮 on 2019-08-30.
//

#ifndef COURIER_CLIENT_GROUPINFO_H
#define COURIER_CLIENT_GROUPINFO_H

#include "predeclare.h"


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

    const std::vector<unsigned int> &getMemberId() const;

    std::string getNickName();

    GroupInfo(unsigned int groupId, const std::string &nickName, const std::string &avatorPath,
              const std::string &notice, const std::vector<unsigned int> &memberId);

    std::string getAvatarPath();

    std::string getNotice();

    void AddUser(UserInfo * user);

    bool HasChat() const;
};


#endif //COURIER_CLIENT_GROUPINFO_H
