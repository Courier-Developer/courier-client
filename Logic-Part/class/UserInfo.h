//
// Created by 孙璋亮 on 2019-08-30.
//

#ifndef COURIER_CLIENT_USEEINFO_H
#define COURIER_CLIENT_USEEINFO_H

#include "User.h"

class UserInfo : public User {
private:
    unsigned int UserId;
    std::string UserName;
    std::string NickName;
    std::string Signature;
    std::string AvatorPath;
    int Status;  //登录状态，是否在线 1在线 0不在线
    int packet;  //所属分组号
    Chat *InChat = nullptr;
    Packet *InPacket = nullptr;
    std::vector<Group *> *InGroups = nullptr;

public:
    const std::string &getAvatorPath() const;

    void setUserId(unsigned int UserId);

    void setUserName(const std::string &UserName);

    virtual ~UserInfo();

    UserInfo();

    void setNickName(const std::string &NickName);

    void setSignature(const std::string &Signature);

    UserInfo(unsigned int UserId, const std::string &UserName, const std::string &NickName,
             const std::string &Signature, const std::string &AvatorPath, int Status, int packet);

    void setAvatorPath(const std::string &AvatorPath);

    void setStatus(int status);

    int getStatus() const;

    UserInfo(unsigned int UserId, const std::string &UserName, const std::string &NickName,
             const std::string &Signature, const std::string &AvatorPath, int status, Chat *InChat = nullptr,
             Packet *InPacket = nullptr,
             std::vector<Group *> *InGroups = nullptr);

    unsigned int getUserId() override;

    std::string getUserName() override;

    std::string getNickName() override;

    std::string getAvatarPath() override;

    UserInfo(unsigned int UserId, const std::string &UserName, const std::string &NickName,
             const std::string &Signature, const std::string &AvatorPath, int status);

    std::string getSignature() override;

    Chat *getChat() override;
};


#endif //COURIER_CLIENT_USEEINFO_H
