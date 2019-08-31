//
// Created by 孙璋亮 on 2019-08-31.
//

#ifndef COURIER_CLIENT_DEALER_H
#define COURIER_CLIENT_DEALER_H

#include "UI-Interface/UserInfo.h"
#include "UI-Interface/ChatInfo.h"
#include "UI-Interface/PacketInfo.h"
#include "UI-Interface/MessageInfo.h"
#include "UI-Interface/GroupInfo.h"
#include <map>
#include <string>

class Dealer {
public:
    static std::map<unsigned int, UserInfo *> UserMap;
    static std::vector<PacketInfo *> PacketList;
    static std::vector<GroupInfo *> GroupList;
    static std::map<int, PacketInfo *> PacketMap;
    static std::map<int, GroupInfo *> GroupMap;
    static std::vector<UserInfo *> UserList;
    static std::vector<ChatInfo *> ChatList;
    static void AddChat(ChatInfo *newchat);
    static UserInfo MyProfile;

    //function for server to call
    static void update_message() ;




    // UI
    static void UI_get_packet_list();
    static void UI_get_group_list();
    static void UI_get_chat_list();
    static void UI_send_message();
    static void UI_get_my_profile();
    static const std::map<unsigned int, UserInfo *> &getUserMap();


private:

    //get something from server or local
    static std::vector<PacketInfo> get_packet_from_server();

    static void update_local_packet(const std::vector<PacketInfo> &packet);

    static void update_local_users(const std::vector<UserInfo> &user);

    static void update_local_group(const std::vector<GroupInfo> &group);

    static void update_local_messages(const std::vector<MessageInfo> &message);

    static void get_information_and_update();

    static void get_user_list_form_local();

    static std::vector<MessageInfo> get_messages_from_local();

    static void get_packet_list();

    static MessageInfo* cope_new_message(const MessageInfo &msg);

    static UserInfo get_my_profile_from_server();

    static std::vector<GroupInfo> get_group_from_server();

    static std::vector<MessageInfo> get_message_from_server();

    static void get_user_list();

    static void get_group_list();

    static void get_message();

    static std::vector<UserInfo> get_users_from_server();

    static void update_local_user();
};

#endif //COURIER_CLIENT_DEALER_H
