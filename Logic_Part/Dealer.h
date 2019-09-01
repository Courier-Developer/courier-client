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
    std::map<unsigned int, UserInfo *> UserMap;
    std::vector<PacketInfo *> PacketList;
    std::vector<GroupInfo *> GroupList;
    std::map<int, PacketInfo *> PacketMap;
    std::map<int, GroupInfo *> GroupMap;
    std::vector<UserInfo *> UserList;
    std::vector<ChatInfo *> ChatList;

    void AddChat(ChatInfo *newchat);

    UserInfo MyProfile;

    //function for server to call
    void update_message();


    // UI
    void UI_get_packet_list();

    void UI_get_group_list();

    void UI_get_chat_list();

    void UI_send_message();

    void UI_get_my_profile();

    const std::map<unsigned int, UserInfo *> &getUserMap();


private:

    //get something from server or local
    std::vector<PacketInfo> get_packet_from_server();

    void update_local_packet(const std::vector<PacketInfo> &packet);

    void update_local_users(const std::vector<UserInfo> &user);

    void update_local_group(const std::vector<GroupInfo> &group);

    void update_local_messages(const std::vector<MessageInfo> &message);

    void get_information_and_update();

    void get_user_list_form_local();

    std::vector<MessageInfo> get_messages_from_local();

    void get_packet_list();

    MessageInfo *cope_new_message(const MessageInfo &msg);

    UserInfo get_my_profile_from_server();

    std::vector<GroupInfo> get_group_from_server();

    std::vector<MessageInfo> get_message_from_server();

    void get_user_list();

    void get_group_list();

    void get_message();

    std::vector<UserInfo> get_users_from_server();

    void update_local_user();

    void log_in(std::string username, std::string password, std::function<void()> success, std::function<void()> fail);

    ChatInfo *get_chat(UserInfo *user);

    ChatInfo *get_chat(GroupInfo *group);
};

#endif //COURIER_CLIENT_DEALER_H
