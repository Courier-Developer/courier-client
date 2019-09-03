//
// Created by 孙璋亮 on 2019-08-31.
//

#include <iostream>
#include "Dealer.h"

/*************************************获取ip**************************************/

std::string Dealer::getip() {
    int sockfd;
    struct sockaddr_in sin;
    struct ifreq ifr;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("socket error");
        exit(1);
    }
    strncpy(ifr.ifr_name, ETH_NAME, IFNAMSIZ);   //Interface name
    if (ioctl(sockfd, SIOCGIFADDR, &ifr) == 0) {  //SIOCGIFADDR 获取interface address
        memcpy(&sin, &ifr.ifr_addr, sizeof(ifr.ifr_addr));
        return inet_ntoa(sin.sin_addr);
    }
}

/*************************************登录初始化*********************************/
//从服务器拉取好友分组信息
std::vector<PacketInfo> Dealer::get_packet_from_server() {
    //call for server
    std::vector<PacketInfo> packets;
    return packets;
}

//登录时拉取初始化信息
void Dealer::get_information_and_update() {
    //MyProfile
    MyProfile = get_my_profile_from_server();
    MyProfileCopy = new UserInfo(MyProfile);

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
    if (UserMap.count(MyProfile.getUserId()) == 0) {
        UserInfo *me = add_user(MyProfile);
        UserMap[MyProfile.getUserId()] = me;
        UserList.push_back(me);
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

//添加聊天会话
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
    tmpmsg->setSender(UserMap[tmpmsg->getSenderId()]);
    if (tmpmsg->getType() == 1) {
        int chatto = tmpmsg->getSenderId();
        if (chatto == MyProfile.getUserId())
            chatto = tmpmsg->getReceiverId();
        //there maybe some bug
        if (UserMap.count(chatto) == 0) {
            std::cerr << "there exists a message can't find the person chat with" << std::endl;
        }
        UserInfo *touser = UserMap[chatto];
        ChatInfo *chat = get_chat(touser);
        tmpmsg->setInChat(chat);
        chat->AddMessage(tmpmsg);
    } else {
        if (tmpmsg->getType() == 2) {
            if (GroupMap.count(tmpmsg->getReceiverId()) == 0) {
                std::cerr << "there exists a message can't find the group chat in" << std::endl;
            }
            GroupInfo *togroup = GroupMap[tmpmsg->getReceiverId()];
            ChatInfo *chat = get_chat(togroup);
            chat->AddMessage(tmpmsg);
            tmpmsg->setInChat(chat);
        } else {
            std::cerr << tmpmsg->getMessageId() << " the message type seems to have some error" << std::endl;
        }
    }
    return tmpmsg;
}

/*********************************获取会话消息（一定要使用这里的获得会话函数)**********************/
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

/************************************好友分组操作******************************/

//通过id获取相应好友分组列表
PacketInfo *Dealer::get_packet_from_id(int packetid) {
    if (PacketMap.count(packetid)) {
        std::cerr << "try to find a no-existed packet by packetid" << std::endl;
        return add_packet(packetid);
    } else {
        return PacketMap[packetid];
    }
}

//添加新分组
PacketInfo *Dealer::add_packet(int packetid, std::string name) {
    PacketInfo *tmppacket = new PacketInfo(name, packetid);
    PacketMap[tmppacket->getPacketId()] = tmppacket;
    PacketList.push_back(tmppacket);
    local_update_packet(*tmppacket);
    if (packetid > 1)
        server_update_packet(*tmppacket);
    return tmppacket;
}

//服务器添加分组
int Dealer::ask_server_to_add_packet(const std::string &packetname) {
    //todo: ask server to add packet
    return packetnum++;
}


PacketInfo *Dealer::UI_add_packet(const std::string &packetname) {
    int packetid = ask_server_to_add_packet(packetname);
    if (packetid) {
        return add_packet(packetid, packetname);
    } else {
        std::cerr << "create packet Error" << std::endl;
        return nullptr;
    }
}

void Dealer::local_update_packet(const PacketInfo &packet) {
    //todo: call for database 有则修改，无则添加
}

void Dealer::server_update_packet(const PacketInfo &packet) {
    //todo: call for server 有则修改，无则添加
}

bool Dealer::UI_change_packetname(PacketInfo *packet, const std::string &name) {
    if (packet->getPacketId() > 0) {
        packet->setPacketName(name);
        local_update_packet(*packet);
        server_update_packet(*packet);
        return 0;
    } else {
        std::cerr << "try to rename <0 packet" << std::endl;
        return 1;
    }
}

bool Dealer::UI_delete_packet(PacketInfo *packet) {
    if (packet->getUsers()->size()) {
        std::cerr << "try to delete a packet with friend" << std::endl;
        return 1;
    } else {
        if (packet->getPacketId() < 2) {
            std::cerr << "try to delete necessary packet" << std::endl;
            return 1;
        } else {
            local_delete_packet(*packet);
            server_delete_packet(*packet);
            return 0;
        }
    }
}

void Dealer::local_delete_packet(const PacketInfo &packet) {
    //todo: call for local database
}

void Dealer::server_delete_packet(const PacketInfo &packet) {
    //todo: call for server
}

/************************************群组**********************************/

//更新群信息
void Dealer::update_groupinfo(const int &groupid, const std::string &name, const std::string &avatorpath,
                              const std::string &notice) {
    GroupInfo *group = GroupMap[groupid];
    group->setNickName(name);
    group->setAvatorPath(avatorpath);
    group->setNotice(notice);
}

//更新本地群信息
void Dealer::update_local_groupinfo(const int &groupid, const std::string &name, const std::string &avatorpath,
                                    const std::string &notice) {
    //todo: call local database
}

//更新服务器群信息
void Dealer::update_server_groupinfo(const int &groupid, const std::string &name, const std::string &avatorpath,
                                     const std::string &notice) {
    //todo: call server
}

//建群
void Dealer::UI_create_group(const std::string &groupname, const std::vector<int> &memberids) {
    int id = ask_server_to_create_group(groupname, memberids);
    GroupInfo *newgroup = add_group(GroupInfo(id, groupname, "", "", memberids));
    update_local_group(*newgroup);
    //todo: call for UI
}

//建群
void Dealer::UI_create_group(const std::string &groupname, const std::vector<UserInfo *> &members) {
    std::vector<int> memberids;
    for (auto &tmp:members) {
        memberids.push_back(tmp->getUserId());
    }
    int id = ask_server_to_create_group(groupname, memberids);
    GroupInfo *newgroup = add_group(GroupInfo(id, groupname, "", "", memberids));
    update_local_group(*newgroup);
    //todo: call for UI
}

//告诉服务器要建群
int Dealer::ask_server_to_create_group(const std::string &name, const std::vector<int> &members) {
    //todo: call for server
    return 10001;
}

//更新本地数据群关系
void Dealer::update_local_group(const GroupInfo &group) {
    //todo: call for local database
}

//被拉进群
void Dealer::be_added_in_group(const GroupInfo &group) {
    GroupInfo *newgroup = add_group(group);
    update_local_group(group);
    //todo: call for UI
}

//离开群
void Dealer::leave_group(GroupInfo *group) {
    if (tell_server_to_leave_group(*group)) {
        local_delete_group(*group);
        group->delete_member(UserMap[MyProfile.getUserId()]);
        if (GroupMap.count(group->getGroupId()))
            GroupMap.erase(group->getGroupId());
        for (auto it = GroupList.begin(); it != GroupList.end(); it++)
            if (*it == group) {
                GroupList.erase(it);
                break;
            }
    }
}

//本地删群
void Dealer::local_delete_group(const GroupInfo &group) {
    //todo: call local database
}

//告诉服务器退群
int Dealer::tell_server_to_leave_group(const GroupInfo &group) {
    //todo: call server
    return 0;
}

//某人离开群
void Dealer::someone_leave_group(const int &groupid, const int &userid) {
    if (GroupMap.count(groupid) && UserMap.count(userid)) {
        GroupMap[groupid]->delete_member(UserMap[userid]);
        //todo: call UI
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
            std::map<int, UserInfo *>::iterator it = UserMap.find(tmpmember);
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

/*************************************好友上下线****************************************************/

void Dealer::someone_online(const int &id) {
    if (UserMap.count(id)) {
        UserInfo *user = UserMap[id];
        user->setStatus(1);
        //todo: call UI
    }
}

void Dealer::someone_offline(const int &id) {
    if (UserMap.count(id)) {
        UserInfo *user = UserMap[id];
        user->setStatus(0);
        //todo: call UI
    }
}


/*************************************添加好友或移动好友分组或搜索好友*********************************/

//用id添加新用户
UserInfo *Dealer::add_user(const int &tmpmember) {
    if (UserMap.count(tmpmember)) {
        std::cerr << "some mistakes, try to add an existed user whose id is " << tmpmember << std::endl;
        return UserMap[tmpmember];
    }
    UserInfo tmpuser = find_user_from_server(tmpmember);
    if (tmpuser.getUserId())
        return add_user(tmpuser);
    else {
        std::cout << "find none" << std::endl;
        return nullptr;
    }
}

//用username添加用户
UserInfo *Dealer::add_user(const std::string &tmpmember) {
    UserInfo tmpuser = find_user_from_server(tmpmember);
    if (tmpuser.getUserId()) {
        if (UserMap.count(tmpuser.getUserId())) {
            std::cerr << "some mistakes, try to add an existed user whose id is " << tmpmember << std::endl;
            return UserMap[tmpuser.getUserId()];
        } else {
            return add_user(tmpuser);
        }
    } else {
        std::cout << "find none" << std::endl;
        return nullptr;
    }
}

//用id向服务器请求对方信息
UserInfo Dealer::find_user_from_server(const int &tmpmember) {
    if (UserMap.count(tmpmember)) {
        std::cerr << "some mistakes, try to find an existed user from server whose id is " << tmpmember << std::endl;
        return *UserMap[tmpmember];
    }
    //todo: get userinfo from the server
    return UserInfo();
}

//用nickname向服务器请求对方信息
UserInfo Dealer::find_user_from_server(const std::string &username) {
    //todo: call for server
    UserInfo user;
    if (UserMap.count(user.getUserId())) {
        std::cerr << "some mistakes, try to find an existed user from server whose id is " << user.getUserId()
                  << std::endl;
        return *UserMap[user.getUserId()];
    } else {
        return user;
    }
}

//添加新成员
UserInfo *Dealer::add_user(const UserInfo &user) {
    if (UserMap.count(user.getUserId()))
        return UserMap[user.getUserId()];
    UserInfo *tmp = new UserInfo(user);
    UserMap[tmp->getUserId()] = tmp;
    UserList.push_back(tmp);
    if (PacketMap.count(tmp->getPacket())) {
        PacketInfo *packet = PacketMap[tmp->getPacket()];
        packet->AddUser(tmp);
        tmp->setInPacket(packet);
    } else {
        PacketInfo *packet = add_packet(tmp->getPacket());
        packet->AddUser(tmp);
        tmp->setInPacket(packet);
    }
    update_local_user(*tmp);
    if (tmp->getPacket() > 0) {
        update_server_user(*tmp);
    }
    return tmp;
}

//更新数据库信息,无则添加，有则修改
void Dealer::update_local_user(const UserInfo &userinfo) {
    //todo: call for local database
}

void Dealer::UI_add_friend(UserInfo *user, int packetid) {
    UI_move_friend(user, packetid);
}

void Dealer::UI_move_friend(UserInfo *user, int packetid) {
    if (PacketMap.count(packetid))
        UI_move_friend(user, PacketMap[packetid]);
    else {
        std::cerr << "don't exist this packet" << std::endl;
    }
}

void Dealer::update_server_user(const UserInfo &user) {
    //todo: call for server to update user
}

void Dealer::update_friend(const UserInfo &user) {   //server_call
    if (UserMap.count(user.getUserId())) {
        UI_move_friend(UserMap[user.getUserId()], PacketMap[user.getPacket()]);
        update_local_user(user);
    } else {
        add_user(user);
    }
    //todo:
//    friendUpdate(UserMap[user.getUserId()]);
}

void Dealer::UI_move_friend(UserInfo *user, PacketInfo *packet) {
    if (user->getInPacket() == packet) {
        std::cerr << "the user does exist in this packet" << std::endl;
        return;
    } else {
        user->getInPacket()->DeleteMember(user);
        user->setInPacket(packet);
        packet->AddUser(user);
        update_local_user(*user);
        update_server_user(*user);
    }
}


void Dealer::UI_add_friend(UserInfo *user, PacketInfo *packet) {
    UI_move_friend(user, packet);
}

//username 和 id 寻找用户
void Dealer::UI_search_user(const std::string &username) {
    UserInfo *tmp = add_user(username);
}

void Dealer::UI_search_user(const int &id) {
    UserInfo *tmp = add_user(id);
}

void Dealer::server_ask_to_add_friend(const UserInfo &user) {
    if (UserMap.count(user.getUserId())) {
        if (user.getPacket() > 0) {
            std::cerr << "does exist this friend" << std::endl;
        }
    } else {
        UserInfo *newuser = add_user(user);
        //todo: call for UI to choose whether to accept
    }
}

void Dealer::UI_accept_add_friend(int userid, PacketInfo *packet) {
    UI_move_friend(UserMap[userid], packet);
}

void Dealer::tell_server_accept_friend(UserInfo newfriend) {
    //todo: call for server
}


void Dealer::friend_be_accepted(const UserInfo &user) {
    if (UserMap.count(user.getUserId())) {
        UI_move_friend(UserMap[user.getUserId()], PacketMap[user.getPacket()]);
    } else {
        add_user(user);
    }
}

/*************************************删除好友**********************************/

//删除好友（实际上仅仅是删除User的好友分组关系，因为好友关系仅仅体现在分组列表上
void Dealer::delete_friend(const int &id) {
    if (UserMap.count(id)) {
        UserInfo *user = UserMap[id];
        delete_friend(user);
    } else {
        std::cerr << "try to delete a no-existed friend!" << std::endl;
        return;
    }
}

//删除好友关系
void Dealer::delete_friend(UserInfo *oldfriend) {
    PacketInfo *oldpacket = oldfriend->getInPacket();
    oldpacket->DeleteMember(oldfriend);
    PacketInfo *stranger = get_packet_from_id(0);
    stranger->AddUser(oldfriend);
    oldfriend->setInPacket(stranger);
}

//删除本地数据
void Dealer::delete_friend(const UserInfo &oldfriend) {
    if (oldfriend.getPacket() != 0 && UserMap.count(oldfriend.getUserId()))
        delete_friend(UserMap[oldfriend.getUserId()]);
    else
        std::cerr << "try to delete a non-existed friend" << std::endl;
}

//UI调用删除,调用我的完成之后再处理UI
void Dealer::UI_delete_friend(UserInfo *oldfriend) {
    //todo: call for server and ask for return value
    local_delete_friend(*oldfriend);
    delete_friend(oldfriend);
}

//服务器请求删除好友
void Dealer::server_delete_friend(const UserInfo &oldfriend) {
    local_delete_friend(oldfriend);
    delete_friend(oldfriend);
    //todo: call for UI
}

//删除本地数据
void Dealer::local_delete_friend(const UserInfo &oldfriend) {
    //todo: call for local database
    return;
}


/*********************************发送消息***********************************/
void Dealer::UI_send_message(int type, const std::string &content, ChatInfo *chat) {
    MessageInfo *newmsg = send_message(type, content, chat);
}

//获得messageid add
int Dealer::send_message_to_server(const MessageInfo &newmsg) {
    //todo: call for server
    return 0;
}

void Dealer::add_local_message(const MessageInfo &newmsg) {
    //todo: update_local_message
}

MessageInfo *Dealer::send_message(int type, const std::string &content, ChatInfo *chat) {
    tm *local;
    time_t t;
    t = time(NULL);
    local = localtime(&t);
    MessageInfo *tmp;
    DateTime sendtime(local->tm_year + 1900, local->tm_mon+1, local->tm_mday, local->tm_hour, local->tm_min,
                      local->tm_sec);
    if (chat->getChatWith() == 1) {
        MessageInfo newmsg = MessageInfo(MyProfile.getUserId(), chat->getToUser()->getUserId(), content, 1, 1, type,
                                         sendtime);
        // maybe some bug here
        int success = send_message_to_server(newmsg);
        if (success)
            newmsg.setMessageId(success);
        else
            newmsg.setStatus(0);
        add_local_message(newmsg);
        tmp = cope_new_message(newmsg);
    } else {
        if (chat->getChatWith() == 2) {
            MessageInfo newmsg = MessageInfo(MyProfile.getUserId(), chat->getToGroup()->getGroupId(), content, 1, 2,
                                             type,
                                             sendtime);
            bool success = send_message_to_server(newmsg);
            if (success) {
                newmsg.setMessageId(success);
            } else {
                newmsg.setStatus(0);
            }
            add_local_message(newmsg);
            tmp = cope_new_message(newmsg);
        } else {
            std::cerr << "Wrong chatType" << std::endl;
        }
    }
    return tmp;
}

/**************************************接收信息************************************/
//todo: add file and pic
void Dealer::receive_new_message(const MessageInfo &msg) {
    add_local_message(msg);
    MessageInfo *newmsg = cope_new_message(msg); //may exist bug here
    //todo: call for UI
}

/**********************************获取云端历史信息*********************************/
void Dealer::UI_get_histroy(ChatInfo *chat) {
    if (chat->getChatWith() > 2 || chat->getChatWith() < 1) {
        std::cerr << "chat to what?" << std::endl;
    } else {
        if (chat->getChatWith() == 1) {
            std::vector<MessageInfo *> msgs = sync_message_histroy(chat->getToUser());
        } else {
            std::vector<MessageInfo *> msgs = sync_message_histroy(chat->getToGroup());
        }
    }
}


//获取会话历史记录
std::vector<MessageInfo> Dealer::get_histroy_of_user_from_server(UserInfo *user) {
    //todo: call for server
    return std::vector<MessageInfo>();
}

std::vector<MessageInfo> Dealer::get_histroy_of_group_from_server(GroupInfo *group) {
    //todo: call for server
    return std::vector<MessageInfo>();
}

//同步内存数据
std::vector<MessageInfo *> Dealer::sync_message_histroy(UserInfo *user) {
    std::vector<MessageInfo *> msgs;
    std::vector<MessageInfo> newmsgs = sync_local_message(user);
    for (auto &tmpmsg:newmsgs) {
        msgs.push_back(cope_new_message(tmpmsg));
    }
    return msgs;
}

std::vector<MessageInfo *> Dealer::sync_message_histroy(GroupInfo *group) {
    std::vector<MessageInfo *> msgs;
    std::vector<MessageInfo> newmsgs = sync_local_message(group);
    for (auto &tmpmsg:newmsgs) {
        msgs.push_back(cope_new_message(tmpmsg));
    }
    return msgs;
}

//同步本地数据库数据
std::vector<MessageInfo> Dealer::sync_local_message(UserInfo *user) {
    //todo: call for the database
    return std::vector<MessageInfo>();
}

std::vector<MessageInfo> Dealer::sync_local_message(GroupInfo *group) {
    //todo: call for the database
    return std::vector<MessageInfo>();
}


/******************************TesT************************************/
UserInfo Dealer::test_create_myprofile() {
    return UserInfo(10001, "ervinxienb", "我，谢神，打钱", "计算几何马斯特就是我！", "", 1, 0);
}

std::vector<PacketInfo> Dealer::test_create_packet() {
    std::vector<PacketInfo> test;
//    std::cout<<"ok!"<<std::endl;
    test.push_back(PacketInfo("黑名单", -1));
//    std::cout<<"ok!"<<std::endl;
    test.push_back(PacketInfo("陌生人", 0));
    test.push_back(PacketInfo("默认分组", 1));
    test.push_back(PacketInfo("附近的人", 2));
    return test;
}

std::vector<UserInfo> Dealer::test_create_users() {
    std::vector<UserInfo> test;
    test.push_back(UserInfo(10002, "ironhead", "大大大铁头", "我的头真铁", "", 0, 1));
    test.push_back(UserInfo(10003, "fountain", "fountain", "no response", "", 1, 2));
    test.push_back(UserInfo(10004, "asdfs", "fousf", "no response", "", 1, 1));
    test.push_back(UserInfo(10005, "fky", "fky", "no response", "", 0, 1));
    test.push_back(UserInfo(10006, "yfh", "yfh", "no response", "", 1, 2));
    test.push_back(UserInfo(10007, "fosdf", "AC自动机fail树上dfs序建可持久化线段树", "CSLnb！", "", 0, -1));
    return test;
}

std::vector<GroupInfo> Dealer::test_create_group() {
    std::vector<GroupInfo> test;
    std::vector<int> members;
    members.push_back(10001), members.push_back(10002), members.push_back(10004);
    test.push_back(GroupInfo(10001, "雀魂交友群", "", "杠上开花", members));
    members.clear();
    members.push_back(10001), members.push_back(10003), members.push_back(10007);
    test.push_back(GroupInfo(10002, "fky粉丝群", "", "膜就完事了", members));
    return test;
}

std::vector<MessageInfo> Dealer::test_create_message() {
    std::vector<MessageInfo> test;
    test.push_back(*(new MessageInfo(10001, 10002, "测试专用场地", 1, 1, 1,  DateTime("2019-08-31 12:31:55"))));
    test.push_back(MessageInfo(10001, 10001, "test", 1, 2, 1, DateTime("2019-08-31 12:31:55")));
    test.push_back(MessageInfo(10002, 10001, "accepted", 1, 2, 1, DateTime("2019-08-31 12:32:05")));
    test.push_back(MessageInfo(10002, 10001, "蛤？", 1, 1, 1, DateTime("2019-08-31 11:32:05")));
    for (auto &tmp:test)
        std::cout<<tmp.getCreateTime().getString()<<std::endl;
    return test;
}

void Dealer::test() {
    //MyProfile
    using std::cout, std::endl;
    MyProfile = test_create_myprofile();
    MyProfileCopy = new UserInfo(MyProfile);
    //PacketInfo
//    std::cout<<"ok!"<<std::endl;
    std::vector<PacketInfo> packets = test_create_packet();
//    std::cout<<"ok!"<<std::endl;
    update_local_packet(packets);
    for (auto &tmp:packets) {
        if (PacketMap.count(tmp.getPacketId())) continue;
        PacketInfo *tmppacket = new PacketInfo(tmp);
        PacketMap[tmppacket->getPacketId()] = tmppacket;
        PacketList.push_back(tmppacket);
    }
//    std::cout<<"ok!"<<std::endl;
    // UserInfo
    std::vector<UserInfo> users = test_create_users();
//    std::cout<<"ok!"<<std::endl;
    update_local_users(users);
//    std::cout<<"ok!"<<std::endl;
    for (auto &tmp:users) {
        if (UserMap.count(tmp.getUserId())) continue;
//        std::cout<<"ok!"<<std::endl;
        UserInfo *tmpuser = new UserInfo(tmp);
//        std::cout<<"ok!"<<std::endl;
        UserMap[tmpuser->getUserId()] = tmpuser;
//        std::cout<<"ok!"<<std::endl;
        UserList.push_back(tmpuser);
//        std::cout<<"ok!"<<std::endl;
        PacketInfo *inpacket = PacketMap[tmpuser->getPacket()];
        //        cout<<tmpuser->getPacket()<<endl;
//        std::cout<<"ok!"<<std::endl;
        inpacket->AddUser(tmpuser);
//        std::cout<<"ok!"<<std::endl;
        tmpuser->setInPacket(inpacket);
    }

    if (UserMap.count(MyProfile.getUserId()) == 0) {
        UserInfo *me = add_user(MyProfile);
        UserMap[MyProfile.getUserId()] = me;
        UserList.push_back(me);
    }

//    std::cout<<"ok!"<<std::endl;
    //GroupInfo
    std::vector<GroupInfo> groups = test_create_group();

//    std::cout<<"ok!"<<std::endl;
    update_local_group(groups);
//    std::cout<<"ok!"<<std::endl;
    for (auto &tmp:groups) {
        if (GroupMap.count(tmp.getGroupId())) continue;

//        std::cout<<"ok!"<<std::endl;
        GroupInfo *tmpgroup = new GroupInfo(tmp);
        GroupList.push_back(tmpgroup);
        GroupMap[tmpgroup->getGroupId()] = tmpgroup;
//        std::cout<<"ok!"<<std::endl;
        for (auto &tmpmember:tmpgroup->getMemberId()) {
//            cout<<tmpmember<<endl;
            UserInfo *memberp = UserMap[tmpmember];
//            cout<<memberp->getUserId()<<endl;
            memberp->setInGroup(tmpgroup);
            tmpgroup->AddUser(memberp);
        }
    }
//    std::cout<<"ok!"<<std::endl;

    //MessageInfo
    std::vector<MessageInfo> messages = test_create_message();
    cout<<messages.size()<<endl;
    for (auto &tmp:messages)
        cout<<tmp.getCreateTime().getString()<<endl;
//    update_local_messages(messages);
//    messages = get_messages_from_local();
    for (auto &tmp:messages) {
        MessageInfo *tmpmsg = cope_new_message(tmp);
        cout<<tmp.getCreateTime().getString()<<endl;
    }
}

void Dealer::ShowTestUserInfo() {
    using std::cout, std::endl;
    cout << endl << endl;
    cout << "***********************UserInfo********************" << endl;
    for (auto &tmp:UserList) {
        cout << tmp->getUserId() << " " << tmp->getNickName() << endl;
        cout << "In Packet " << tmp->getInPacket()->getPacketName() << endl;
        cout << "Whether there is a chat: " << tmp->HasChat() << endl;
        cout << "In Groups:";
        for (auto &ingroup:(*tmp->getInGroups()))
            cout << " " << ingroup->getNickName();
        cout << endl;
        cout << "Status: " << tmp->getStatus() << endl;
        cout << "---------------------------------------------------" << endl;
    }
}

void Dealer::ShowTestGroupInfo() {
    using std::cout, std::endl;
    cout << endl << endl;
    cout << "***********************GroupInfo********************" << endl;
    for (auto &group:GroupList) {
        cout << group->getGroupId() << " " << group->getNickName() << endl;
        cout << "In this Group: " << endl;
        for (auto &tmp:(*group->getUsers())) {
            cout << "      ID: " << tmp->getUserId() << "     NickName: " << tmp->getNickName() << endl;
        }
        cout << "Members' id:";
        for (auto &tmp:(group->getMemberId())) cout << " " << tmp;
        cout << endl;
        cout << "Whether there is a chat: " << group->HasChat() << endl;
        cout << "Notice:    " << group->getNotice() << endl;
        cout << "---------------------------------------------------" << endl;
    }
}

void Dealer::ShowTestPacketInfo() {
    using std::cout, std::endl;
    cout << endl << endl;
    cout << "***********************PacketInfo********************" << endl;
    for (auto &tmp:PacketList) {
        cout << " ID: " << tmp->getPacketId() << "  Name: " << tmp->getPacketName() << endl;
        cout << " Members:";
        for (auto &tmpmember:(*tmp->getUsers()))
            cout << " " << tmpmember->getNickName();
        cout << endl;
        cout << "----------------------------------------------------" << endl;

    }

}

void Dealer::ShowTestChatInfo() {
    using std::cout, std::endl;
    cout << endl << endl;
    cout << "***********************ChatInfo********************" << endl;
    for (auto &tmp:ChatList) {
        cout << "Chat with ";
        if (tmp->getChatWith() == 1) {
            cout << "User" << endl;
            cout << "   ID: " << tmp->getToUser()->getUserId() << "  NickName: " << tmp->getToUser()->getNickName()
                 << endl;
        } else {
            if (tmp->getChatWith() == 2) {
                cout << "Group" << endl;
                cout << "  ID: " << tmp->getToGroup()->getGroupId() << "  NickName: " << tmp->getToGroup()->getGroupId()
                     << endl;
            } else {
                cout << "Error" << endl;
            }
        }
        cout << "Number of Message: " << (*tmp->getMsgList()).size() << endl;
        cout << "Content: " << endl;
        for (auto *msgs:(*tmp->getMsgList())) {
            cout << "  " << msgs->getSender()->getNickName() << ": " << msgs->getContent() <<"  "<<msgs->getCreateTime().getString() <<endl;
        }
        cout << "--------------------------------------------------" << endl;
    }
}

/******************************Attention******************************/
//UI的会话消息需要调用我的函数，不能直接使用数据否则会话列表可能发生错误


/***********************************UI-Interface**************************************/

//登录
void Dealer::login(const std::string &username, const std::string &password,
                   std::function<void(std::vector<PacketInfo *> &, std::vector<GroupInfo *> &,
                                      std::vector<ChatInfo *> &)> success, std::function<void(std::string)> fail) {



    //todo:
    if (/*****/1) {
//        get_information_and_update();
        test();
        success(PacketList, GroupList, ChatList);
    } else {
        fail("不知道出了什么问题，反正就是登录失败了！");
    }
}


void
Dealer::getMyprofile(std::function<void(UserInfo *)> getprofile, std::function<void(std::string)> error) {
    if (MyProfile.getUserId() != 0)
        getprofile(MyProfileCopy);
    else {
        error("还未获得个人信息");
    }
}

void Dealer::queryUser(int id, std::function<void(UserInfo *)> success, std::function<void(std::string)> fail) {
    UserInfo *user = add_user(id);
    if (user)
        success(user);
    else
        fail("查无此人");
}

void Dealer::addFriend(int id, std::function<void(std::string)> success, std::function<void(std::string)> fail) {
    //todo:
    if (/*******/1 && (!UserMap.count(id) || UserMap[id]->getPacket() != 0)) {
        success("我觉得可以");
    } else {
        fail("我觉得不行");
    }
}

void Dealer::agreefriend(int id, std::function<void(UserInfo *)> success, std::function<void(std::string)> fail) {
    //todo:
    if (/*********/1 && (!UserMap.count(id) || UserMap[id]->getPacket() != 0)) {
        UI_move_friend(add_user(id), 1);
        success(UserMap[id]);
    } else {
        fail("我觉得不行");
    }
}

void Dealer::deleteFriend(int id, std::function<void(std::string)> success, std::function<void(std::string)> fail) {
    //todo:
    if (/********/ 1) {
        UI_delete_friend(UserMap[id]);
        success("我觉得可以");
    } else {
        fail("我觉得不行");
    }
}

void Dealer::chatWith(UserInfo * user, std::function<void(ChatInfo *)> success, std::function<void(std::string)> fail) {
    success(get_chat(user));
}

void
Dealer::chatWith(GroupInfo *group, std::function<void(ChatInfo *)> success, std::function<void(std::string)> fail) {
    success(get_chat(group));
}

void Dealer::moveToPacket(UserInfo *user, PacketInfo *packet, std::function<void(std::string)> success,
                          std::function<void(std::string)> fail) {
    if (user->getInPacket()!=packet){
        UI_move_friend(user,packet);
        success("可能可以");
    }else{
        fail("这样不行");
    }
}

void
Dealer::addPacket(std::string name, std::function<void(PacketInfo *)> success, std::function<void(std::string)> fail) {
    PacketInfo *packet=UI_add_packet(name);
    if (packet)
        success(packet);
    else
        fail("我觉得不行");
}

void Dealer::renamePacket(std::string name, PacketInfo *packet, std::function<void(std::string)> success,
                          std::function<void(std::string)> fail) {
    if (UI_change_packetname(packet,name))
        fail("这样不行");
    else
        success("好像可以");
}

void
Dealer::deletePacket(PacketInfo *packet, std::function<void(std::string)> ok, std::function<void(std::string)> fail) {
    if (UI_delete_packet(packet))
        fail("这样不行");
    else
        ok("好像可以");
}











