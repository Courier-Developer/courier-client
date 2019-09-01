//
// Created by 孙璋亮 on 2019-08-31.
//

#include <iostream>
#include "Dealer.h"



std::vector<PacketInfo> Dealer::get_packet_from_server() {
    //call for server
    std::vector<PacketInfo> packets;
    return packets;
}


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

UserInfo Dealer::get_my_profile_from_server() {
    //todo: call for server
    UserInfo myprofile;
    return myprofile;
}

void Dealer::AddChat(ChatInfo *newchat) {
    ChatList.push_back(newchat);
}

void Dealer::update_local_packet(const std::vector<PacketInfo> &packet) {
    // todo: call for local database
}

std::vector<UserInfo> Dealer::get_users_from_server() {
    //todo: call for the server
    std::vector<UserInfo> users;
    return users;
}

void Dealer::update_local_users(const std::vector<UserInfo> &user) {
    //todo: call for local database
}

std::vector<GroupInfo> Dealer::get_group_from_server() {
    //todo: call for the server
    std::vector<GroupInfo> groups;
    return groups;
}

void Dealer::update_local_group(const std::vector<GroupInfo> &group) {
    //todo: call for the local database
}

std::vector<MessageInfo> Dealer::get_message_from_server() {
    //todo: call for the server;
    std::vector<MessageInfo> messages;
    return messages;
}

void Dealer::update_local_messages(const std::vector<MessageInfo> &message) {
    //todo: call for the local database
}

std::vector<MessageInfo> Dealer::get_messages_from_local() {
    //todo: call for the local database
    std::vector<MessageInfo> msgs;
    return msgs;
}

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

ChatInfo *Dealer::get_chat(UserInfo *user) {
    if (user->HasChat())
        return user->getChat();
    else {
        ChatInfo *tmpchat = user->getChat();
        ChatList.push_back(tmpchat);
        return tmpchat;
    }
}

ChatInfo *Dealer::get_chat(GroupInfo *group) {
    if (group->HasChat())
        return group->getChat();
    else {
        ChatInfo *tmpchat=group->getChat();
        ChatList.push_back(tmpchat);
        return tmpchat;
    }
}




