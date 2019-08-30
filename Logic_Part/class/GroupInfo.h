//
// Created by 孙璋亮 on 2019-08-30.
//

#ifndef COURIER_CLIENT_GROUPINFO_H
#define COURIER_CLIENT_GROUPINFO_H


#include <Group.h>

class GroupInfo: public Group {
private:
    unsigned int GroupId;
    std::string NickName;
    std::string AvatorPath;
    std::string Notice;
    std::vector<unsigned int> MemberId;
    Chat *chat;
    std::vector<User *> *Members;
public:
    std::vector<User *> *getUsers() override;

    Chat *getChat() override;

    virtual ~GroupInfo();

    GroupInfo();

    unsigned int getGroupId() override;

    GroupInfo(unsigned int GroupId, const std::string &NickName, const std::string &AvatorPath,
              const std::string &Notice, const std::vector<unsigned int> &MemberId, Chat *chat,
              std::vector<User *> *Members);

    std::string getNickName() override;

    std::string getAvatarPath() override;

    std::string getNotice() override;
};


#endif //COURIER_CLIENT_GROUPINFO_H
