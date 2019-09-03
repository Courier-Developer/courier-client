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
#include <cstring>
#include <functional>
#include <net/if.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>

#define ETH_NAME    "eth0"
//#include "FeverRPC/utils.cpp"
//#include "FeverRPC/lock.cpp"
//#include "FeverRPC/feverrpc.cpp"

class Dealer {
private:
    int packetnum = 1;
    std::string ip;

//    FeverRPC::Client client;
    std::string getip();

    std::vector<PacketInfo> get_packet_from_server();

    void update_local_packet(const std::vector<PacketInfo> &packet);

    void update_local_users(const std::vector<UserInfo> &user);

    void update_local_group(const std::vector<GroupInfo> &group);

    void update_local_messages(const std::vector<MessageInfo> &message);

    void get_information_and_update();

    std::vector<MessageInfo> get_messages_from_local();

    MessageInfo *cope_new_message(const MessageInfo &msg);

    UserInfo get_my_profile_from_server();

    std::vector<GroupInfo> get_group_from_server();

    std::vector<MessageInfo> get_message_from_server();

    GroupInfo *add_group(GroupInfo newgroup);

    std::vector<UserInfo> get_users_from_server();

    UserInfo *add_user(const int &tmpmember);

    UserInfo *add_user(const std::string &tmpmember);

    UserInfo find_user_from_server(const int &tmpmember);

    UserInfo find_user_from_server(const std::string &username);

    UserInfo *add_user(const UserInfo &user);

    PacketInfo *add_packet(int packetid, std::string name = "Stranger");

    void delete_friend(const int &id);

    void delete_friend(UserInfo *oldfriend);

    void delete_friend(const UserInfo &oldfriend);

    PacketInfo *get_packet_from_id(int packetid);

    void local_delete_friend(const UserInfo &oldfriend);

    void update_local_user(const UserInfo &userinfo);

    void update_server_user(const UserInfo &user);

    int send_message_to_server(const MessageInfo &newmsg);

    void add_local_message(const MessageInfo &newmsg);

    MessageInfo *send_message(int type, const std::string &content, ChatInfo *chat);

    std::vector<MessageInfo> get_histroy_of_user_from_server(UserInfo *user);

    std::vector<MessageInfo> get_histroy_of_group_from_server(GroupInfo *group);

    std::vector<MessageInfo *> sync_message_histroy(UserInfo *user);

    std::vector<MessageInfo *> sync_message_histroy(GroupInfo *group);

    std::vector<MessageInfo> sync_local_message(UserInfo *user);

    std::vector<MessageInfo> sync_local_message(GroupInfo *group);

    int ask_server_to_add_packet(const std::string &packetname);

    void local_update_packet(const PacketInfo &packet);

    void server_update_packet(const PacketInfo &packet);

    void local_delete_packet(const PacketInfo &packet);

    void server_delete_packet(const PacketInfo &packet);

    void tell_server_accept_friend(UserInfo newfriend);

    int ask_server_to_create_group(const std::string &name, const std::vector<int> &members);

    /******************************************Test**************************************/
    UserInfo test_create_myprofile();

    std::vector<PacketInfo> test_create_packet();

    std::vector<UserInfo> test_create_users();

    std::vector<GroupInfo> test_create_group();

    std::vector<MessageInfo> test_create_message();

    /************************************************************************************/

    void UI_accept_add_friend(int userid, PacketInfo *packet);

    void AddChat(ChatInfo *newchat);

    void UI_send_message(int type, const std::string &content, ChatInfo *chat);

    void UI_delete_friend(UserInfo *oldfriend);

    ChatInfo *get_chat(UserInfo *user);

    ChatInfo *get_chat(GroupInfo *group);

    void UI_add_friend(UserInfo *user, int packetid = 1);

    void UI_move_friend(UserInfo *user, int packetid = 1);

    void UI_add_friend(UserInfo *user, PacketInfo *packet);

    void UI_move_friend(UserInfo *user, PacketInfo *packet);

    void UI_search_user(const std::string &username);

    void UI_search_user(const int &id);

    void UI_get_histroy(ChatInfo *chat);

    PacketInfo *UI_add_packet(const std::string &packetname);

    bool UI_change_packetname(PacketInfo *packet, const std::string &name);

    bool UI_delete_packet(PacketInfo *packet);

    void UI_create_group(const std::string &groupname, const std::vector<int> &memberids);

    void UI_create_group(const std::string &groupname, const std::vector<UserInfo *> &members);

    void update_local_group(const GroupInfo &group);

    void leave_group(GroupInfo *group);

    void local_delete_group(const GroupInfo &group);

    int tell_server_to_leave_group(const GroupInfo &group);

    void update_groupinfo(const int &groupid, const std::string &name, const std::string &avatorpath,
                          const std::string &notice);

    void update_local_groupinfo(const int &groupid, const std::string &name, const std::string &avatorpath,
                                const std::string &notice);

    void update_server_groupinfo(const int &groupid, const std::string &name, const std::string &avatorpath,
                                 const std::string &notice);

public:
    /************************************** Data ***************************************/
    std::map<int, UserInfo *> UserMap;
    std::vector<PacketInfo *> PacketList;
    std::vector<GroupInfo *> GroupList;
    std::map<int, PacketInfo *> PacketMap;
    std::map<int, GroupInfo *> GroupMap;
    std::vector<UserInfo *> UserList;
    std::vector<ChatInfo *> ChatList;
    UserInfo MyProfile;
    UserInfo MyProfileCopy;

    /************************************** UI ***************************************/


    void login(const std::string &username, const std::string &password,
               std::function<void(std::vector<PacketInfo *> &, std::vector<GroupInfo *> &,
                                  std::vector<ChatInfo *> &)> success, std::function<void(std::string)> fail);


    void getMyprofile(std::function<void(const UserInfo &)> getprofile, std::function<void(std::string)> error);

    void queryUser(int id, std::function<void(UserInfo *)> success, std::function<void(std::string)> fail);

    void addFriend(int id, std::function<void(std::string)> success, std::function<void(std::string)> fail);

    void agreefriend(int id, std::function<void(UserInfo *)> success, std::function<void(std::string)> fail);

    void deleteFriend(int id, std::function<void(std::string)> success, std::function<void(std::string)> fail);

    void chatWith(UserInfo *user, std::function<void(ChatInfo *)> success, std::function<void(std::string)> fail);

    void chatWith(GroupInfo *group, std::function<void(ChatInfo *)> success, std::function<void(std::string)> fail);

    void moveToPacket(UserInfo *user, PacketInfo *packet, std::function<void(std::string)> success,
                      std::function<void(std::string)> fail);

    void addPacket(std::string name,std::function<void(PacketInfo*)> success,std::function<void(std::string)> fail);

    void renamePacket(std::string name,PacketInfo* packet,std::function<void(std::string)>success,std::function<void(std::string)> fail);

    void deletePacket(PacketInfo* packet,std::function<void(std::string)> ok,std::function<void(std::string)> fail);
    /**************************************Server*************************************/

    void server_ask_to_add_friend(const UserInfo &user);

    void server_delete_friend(const UserInfo &oldfriend);

    void receive_new_message(const MessageInfo &msg);

    void friend_be_accepted(const UserInfo &user);

    void be_added_in_group(const GroupInfo &group);

    void someone_leave_group(const int &groupid, const int &userid);

    void someone_online(const int &id);

    void someone_offline(const int &id);

    void update_friend(const UserInfo &user);

    /**************************************Test*************************************/

    void test();

    void ShowTestUserInfo();

    void ShowTestGroupInfo();

    void ShowTestPacketInfo();

    void ShowTestChatInfo();

    /*******************************************************************************/
};

#endif //COURIER_CLIENT_DEALER_H
