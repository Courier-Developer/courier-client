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
//#include "FeverRPC/utils.cpp"
//#include "FeverRPC/lock.cpp"
//#include "FeverRPC/feverrpc.cpp"

class Dealer {
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

    GroupInfo* add_group(GroupInfo newgroup);

    std::vector<UserInfo> get_users_from_server();

    void update_local_user();

    void log_in(std::string username, std::string password, std::function<void()> success, std::function<void()> fail);

    UserInfo *add_user(const unsigned int &tmpmember);

    UserInfo *add_user(const std::string &tmpmember);

    UserInfo find_user_from_server(const unsigned int &tmpmember);

    UserInfo find_user_from_server(const std::string &username);

    UserInfo *add_user(UserInfo user);

    PacketInfo *add_packet(int packetid,std::string name="Stranger");

    void delete_friend(const unsigned int &id);

    void delete_friend(UserInfo *oldfriend);

    void delete_friend(UserInfo oldfriend);

    PacketInfo *get_packet_from_id(int packetid);

    void local_delete_friend(const UserInfo& oldfriend);

    void update_local_user(UserInfo userinfo);

    bool send_message_to_server(const MessageInfo &newmsg);

    void add_local_message(const MessageInfo &newmsg);

    MessageInfo* send_message(const std::string &content,ChatInfo *chat);

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

    void UI_send_message(const std::string &content,ChatInfo* chat);

    void UI_get_my_profile();

    void UI_log_in(std::string username,std::string password);

    void UI_add_friend();

    void UI_delete_friend();

    void UI_delete_friend(UserInfo *oldfriend);

    void server_delete_friend(const UserInfo& oldfriend);

    ChatInfo *get_chat(UserInfo *user);

    ChatInfo *get_chat(GroupInfo *group);

    void UI_add_friend(UserInfo *user,int packetid=1);

    void UI_move_friend(UserInfo *user,int packetid=1);

    void UI_add_friend(UserInfo *user,PacketInfo* packet);

    void UI_move_friend(UserInfo *user,PacketInfo* packet);

    void UI_search_user(const std::string &username);

    void UI_search_user(const unsigned int& id);
};

#endif //COURIER_CLIENT_DEALER_H
