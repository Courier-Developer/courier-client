//
// Created by 孙璋亮 on 2019-08-30.
//

#ifndef COURIER_CLIENT_USEEINFO_H
#define COURIER_CLIENT_USEEINFO_H

#include "predeclare.h"
#include "User.h"
#include "GroupInfo.h"
#include "PacketInfo.h"
#include "ChatInfo.h"

class UserInfo : public User {
private:
    unsigned int UserId;
    std::string UserName;
    std::string NickName;
    std::string Signature;
    std::string AvatorPath;
    int Status;  //登录状态，是否在线 1在线 0不在线
    int packet;  //所属分组号
    ChatInfo *InChat = nullptr;
    PacketInfo *InPacket = nullptr;
    std::vector<GroupInfo *> *InGroups = nullptr;

public:
    const std::string &getAvatorPath() const;

    void setUserId(unsigned int UserId);

    void setUserName(const std::string &UserName);

    virtual ~UserInfo();

    UserInfo();

    void setNickName(const std::string &NickName);

    void setSignature(const std::string &Signature);

    void setAvatorPath(const std::string &AvatorPath);

    void setStatus(int status);

    int getStatus() const;

    unsigned int getUserId() override;

    std::string getUserName() override;

    std::string getNickName() override;

    std::string getAvatarPath() override;

    std::string getSignature() override;

    Chat *getChat() override;
};


#endif //COURIER_CLIENT_USEEINFO_H
