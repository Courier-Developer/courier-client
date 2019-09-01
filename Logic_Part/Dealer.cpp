//
// Created by 孙璋亮 on 2019-08-31.
//

#include <iostream>
#include "Dealer.h"

//从服务器拉取好友分组信息
std::vector<PacketInfo> Dealer::get_packet_from_server() {
    //call for server
    std::vector<PacketInfo> packets;
    return packets;
}

//登录时我拉取初始化信息
void Dealer::get_information_and_update() {
    //MyProfile
    UserInfo myprofile = get_my_profile_from_server();
    MyProfile = myprofile;

    //PacketInfo
    std::vector<PacketInfo> packets = get_packet_from_server();
    update_local_packet(packets);
    for (auto &tmp:packets) {
        if (PacketMap.count(tmp.getPacketId())) continue;
        PacketInfo *tmppacket = new PacketInfo(tmp);
        PacketMap[tmppacket->getPacketId()] = tmppacket;
        PacketList.push_back(tmppacket);
    }

    // UserInfo
    std::vector<UserInfo> users = get_users_from_server();
    update_local_users(users);
    for (auto &tmp:users) {
        if (UserMap.count(tmp.getUserId())) continue;
        UserInfo *tmpuser = new UserInfo(tmp);
        UserMap[tmpuser->getUserId()] = tmpuser;
        UserList.push_back(tmpuser);
        PacketInfo *inpacket = PacketMap[tmpuser->getPacket()];
        inpacket->AddUser(tmpuser);
        tmpuser->setInPacket(inpacket);
    }

    //GroupInfo
    std::vector<GroupInfo> groups = get_group_from_server();
    update_local_group(groups);
    for (auto &tmp:groups) {
        if (GroupMap.count(tmp.getGroupId())) continue;
        GroupInfo *tmpgroup = new GroupInfo(tmp);
        GroupList.push_back(tmpgroup);
        GroupMap[tmpgroup->getGroupId()] = tmpgroup;
        for (auto &tmpmember:tmpgroup->getMemberId()) {
            UserInfo *memberp = UserMap[tmpmember];
            memberp->setInGroup(tmpgroup);
            tmpgroup->AddUser(memberp);
        }
    }


    //MessageInfo
    std::vector<MessageInfo> messages = get_message_from_server();
    update_local_messages(messages);
    messages = get_messages_from_local();
    for (auto &tmp:messages) {
        MessageInfo *tmpmsg = cope_new_message(tmp);
    }
}

//从服务器获取我的个人信息
UserInfo Dealer::get_my_profile_from_server() {
    //todo: call for server
    UserInfo myprofile;
    return myprofile;
}

//添加聊天回话
void Dealer::AddChat(ChatInfo *newchat) {
    ChatList.push_back(newchat);
}

//更新本地好友分组信息
void Dealer::update_local_packet(const std::vector<PacketInfo> &packet) {
    // todo: call for local database
}

//从服务端获取有关用户信息
std::vector<UserInfo> Dealer::get_users_from_server() {
    //todo: call for the server
    std::vector<UserInfo> users;
    return users;
}

//更新用户信息到数据库
void Dealer::update_local_users(const std::vector<UserInfo> &user) {
    //todo: call for local database
}

//从服务端获取群组信息
std::vector<GroupInfo> Dealer::get_group_from_server() {
    //todo: call for the server
    std::vector<GroupInfo> groups;
    return groups;
}

//更新本地群组信息
void Dealer::update_local_group(const std::vector<GroupInfo> &group) {
    //todo: call for the local database
}

//从服务端获取消息信息
std::vector<MessageInfo> Dealer::get_message_from_server() {
    //todo: call for the server;
    std::vector<MessageInfo> messages;
    return messages;
}

//更新本地消息信息
void Dealer::update_local_messages(const std::vector<MessageInfo> &message) {
    //todo: call for the local database
}

//从本地获取消息信息
std::vector<MessageInfo> Dealer::get_messages_from_local() {
    //todo: call for the local database
    std::vector<MessageInfo> msgs;
    return msgs;
}

//处理新信息
MessageInfo *Dealer::cope_new_message(const MessageInfo &msg) {
    MessageInfo *tmpmsg = new MessageInfo(msg);
    if (tmpmsg->getType() == 1) {
        unsigned int chatto = tmpmsg->getSenderId();
        if (chatto == MyProfile.getUserId())
            chatto = tmpmsg->getReceiverId();
        UserInfo *touser = UserMap[chatto];
        ChatInfo *chat = get_chat(touser);
        chat->AddMessage(tmpmsg);
    } else {
        if (tmpmsg->getType() == 2) {
            GroupInfo *togroup = GroupMap[tmpmsg->getReceiverId()];
            ChatInfo *chat = get_chat(togroup);
            chat->AddMessage(tmpmsg);
        } else {
            std::cerr << tmpmsg->getMessageId() << " the message type seems to have some error" << std::endl;
        }
    }
    return tmpmsg;
}

//获取用户会话信息
ChatInfo *Dealer::get_chat(UserInfo *user) {
    if (user->HasChat())
        return user->getChat();
    else {
        ChatInfo *tmpchat = user->getChat();
        ChatList.push_back(tmpchat);
        return tmpchat;
    }
}

//获取群组会话信息
ChatInfo *Dealer::get_chat(GroupInfo *group) {
    if (group->HasChat())
        return group->getChat();
    else {
        ChatInfo *tmpchat = group->getChat();
        ChatList.push_back(tmpchat);
        return tmpchat;
    }
}

//添加新群组
GroupInfo *Dealer::add_group(GroupInfo newgroup) {
    if (GroupMap.count(newgroup.getGroupId())) {
        std::cerr << "Maybe something is wrong, there seems to be a same group" << std::endl;
        return GroupMap[newgroup.getGroupId()];
    } else {
        GroupInfo *tmpgroup = new GroupInfo(newgroup);
        GroupMap[tmpgroup->getGroupId()] = tmpgroup;
        GroupList.push_back(tmpgroup);
        for (auto &tmpmember:tmpgroup->getMemberId()) {
            std::map<unsigned int, UserInfo *>::iterator it = UserMap.find(tmpmember);
            if (it == UserMap.end()) {
                UserInfo *tmp = add_user(tmpmember);
                tmp->setInGroup(tmpgroup);
                tmpgroup->AddUser(tmp);
            } else {
                UserInfo *tmp = it->second;
                tmp->setInGroup(tmpgroup);
                tmpgroup->AddUser(tmp);
            }
        }
        return tmpgroup;
    }
}

//用id添加新用户
UserInfo *Dealer::add_user(const unsigned int &tmpmember) {
    if (UserMap.count(tmpmember)) {
        std::cerr << "some mistakes, try to add an existed user whose id is " << tmpmember << std::endl;
        return UserMap[tmpmember];
    }
    UserInfo tmpuser = find_user_from_server(tmpmember);
    return add_user(tmpuser);
}


//用id向服务器请求对方信息
UserInfo Dealer::find_user_from_server(const unsigned int &tmpmember) {
    if (UserMap.count(tmpmember)) {
        std::cerr << "some mistakes, try to find an existed user from server whose id is " << tmpmember << std::endl;
        return *UserMap[tmpmember];
    }
    //todo: get userinfo from the server
    return UserInfo();
}


//好友分组添加新成员
UserInfo *Dealer::add_user(UserInfo user) {
    UserInfo *tmp = new UserInfo(user);
    if (PacketMap.count(tmp->getPacket())) {
        PacketInfo *packet = PacketMap[tmp->getPacket()];
        packet->AddUser(tmp);
        tmp->setInPacket(packet);
    } else {
        PacketInfo *packet = add_packet(tmp->getPacket());
        packet->AddUser(tmp);
        tmp->setInPacket(packet);
    }
    return tmp;
}

// 通过id获取相应好友分组列表
PacketInfo *Dealer::get_packet_from_id(int packetid) {
    if (PacketMap.count(packetid)){
        std::cerr<<"try to find a no-existed packet by packetid"<<std::endl;
        return nullptr;
    } else{
        return  PacketMap[packetid];
    }
}


//添加新分组
PacketInfo *Dealer::add_packet(int packetid, std::string name) {
    PacketInfo *tmppacket = new PacketInfo(name, packetid);
    PacketMap[tmppacket->getPacketId()] = tmppacket;
    PacketList.push_back(tmppacket);
    return tmppacket;
}




//删除好友（实际上仅仅是删除User的好友分组关系，因为好友关系仅仅体现在分组列表上
void Dealer::delete_friend(const unsigned int &id) {
    if (UserMap.count(id)) {
        UserInfo *user = UserMap[id];
        delete_friend(user);
    } else {
        std::cerr << "try to delete a no-existed friend!" << std::endl;
        return;
    }
}

void Dealer::delete_friend(UserInfo *) {
}





