//
// Created by 孙璋亮 on 2019-08-30.
//

#ifndef COURIER_CLIENT_UI_PART_H
#define COURIER_CLIENT_UI_PART_H

#include <Message.h>
#include "Logic_Part.h"

class UI_Part {
private:
    Logic_Part &Logic;
public:
    void bind(const Logic_Part &L) {
        Logic = L;
        L.bind(this);
    }

    virtual void SigninSuccess() = 0; //注册成功，失败会调用Error
    virtual void LoginSuccess() = 0; //登录成功
    virtual void Error(std::string warningInfo) = 0; //出现错误，参数是错误提示信息
    virtual void MyProfile(const User &me) = 0; //给UI自己的个人资料
    virtual void ContactListInfo(const std::vector<Group> &groups, const std::vector<Packet> &packets) = 0; //给联系人列表
    virtual void ChatListInfo(const std::vector<Chat> &chats) = 0; //会话列表
    virtual void GiveChat(const Chat &chat) = 0;  //与某人的会话信息
    virtual void ReceiveMsg(const Message &NewMsg) = 0; //收到信息
    virtual void NewFriend(const User &NewFri) = 0; //添加了新好友
    virtual void BeDeleted(User who) = 0; //被Who删好友了
    virtual void BeInGroup(const Group &group) = 0; //被拉到某个群
    virtual void DetailInfo(const User &who) = 0; //他人的详细信息
    virtual void UpdateProfileSuccess() = 0;  //修改个人资料成功
    virtual void SendMsgSuccess() = 0; //发送信息成功
    virtual void SendMsgFail() = 0; //发送信息失败

};


#endif //COURIER_CLIENT_UI_PART_H
