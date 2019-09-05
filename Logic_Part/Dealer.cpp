//
// Created by 孙璋亮 on 2019-08-31.
//


#include "../UI-part/View/implement.h"
#include "../file/MyFile.h"

/*************************************获取ip**************************************/


/*************************************登录初始化*********************************/
//从服务器拉取好友分组信息
std::vector<PacketInfo> Dealer::get_packet_from_server() {
    //call for server
    auto v = client.call<std::vector<package> >("get_all_my_package");
    std::cout << v.size() << std::endl;
    std::vector<PacketInfo> packets = Convert::cv_vpacket_to_client(v);
    std::cout << packets.size() << std::endl;
    for (auto &tmp:packets)
        std::cout << tmp.getPacketId() << std::endl;
    return packets;
}

//登录时拉取初始化信息
void Dealer::get_information_and_update() {
    //MyProfile

    MyProfile = get_my_profile_from_server();
    MyProfileCopy = new UserInfo(MyProfile);
    //PacketInfo
    UserMap[MyProfileCopy->getUserId()] = MyProfileCopy;
    PacketMap[0] = new PacketInfo("stranger", 0);
    PacketMap[0]->AddUser(MyProfileCopy);
    MyProfileCopy->setInPacket(PacketMap[0]);
    std::vector<PacketInfo> packets = get_packet_from_server();
    update_local_packet(packets);
    for (auto &tmp:packets) {
        if (PacketMap.count(tmp.getPacketId())) continue;
        PacketInfo *tmppacket = new PacketInfo(tmp);
        PacketMap[tmppacket->getPacketId()] = tmppacket;
        PacketList.push_back(tmppacket);
        cout << tmp.getPacketId() << std::endl;
    }

    // UserInfo
    std::vector<UserInfo> users = get_users_from_server();
    for (auto &tmp:users)
        std::cout << tmp.getNickName() << " " << tmp.getUserId() << " " << std::endl;
//    update_local_users(users);
    for (auto &tmp:users) {
        if (UserMap.count(tmp.getUserId())) continue;
        UserInfo *tmpuser = new UserInfo(tmp);
        UserMap[tmpuser->getUserId()] = tmpuser;
        UserList.push_back(tmpuser);
//        if (PacketMap.count(tmpuser->getPacket())==0)
        PacketInfo *inpacket = PacketMap[tmpuser->getPacket()];
        inpacket->AddUser(tmpuser);
        tmpuser->setInPacket(inpacket);
    }
    if (UserMap.count(MyProfile.getUserId()) == 0) {
        UserInfo *me = add_user(MyProfile);
        UserMap[MyProfile.getUserId()] = me;
        UserList.push_back(me);
    }

    //todo:
    //GroupInfo
    std::vector<GroupInfo> groups = get_group_from_server();
//    update_local_group(groups);
    std::cout << groups.size() << std::endl;
    for (auto &tmp:groups) {
        std::cout << "ok" << std::endl;
        add_group(tmp);
    }

    std::cout << "ok" << std::endl;
    //MessageInfo
    std::vector<MessageInfo> messages = get_message_from_server();
    for (auto &tmp:messages) {
        MessageInfo *tmpmsg = cope_new_message(tmp);
    }
}

//从服务器获取我的个人信息
UserInfo Dealer::get_my_profile_from_server() {
    //todo: call for server
    auto xxx = client.call<userinfo>("get_my_info");
    UserInfo myprofile = Convert::cv_user_to_client(xxx);
    std::cout << myprofile.getNickName() << std::endl;
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
    auto xxx = client.call<vector<Friend> >("get_all_friends_info");
    std::vector<UserInfo> users = Convert::cv_vfriend_to_client(xxx);
    for (auto &tmp:users)
        std::cout << tmp.getNickName() << " " << tmp.getPacket() << endl;
    return users;
}

//更新用户信息到数据库
void Dealer::update_local_users(const std::vector<UserInfo> &user) {
    //todo: call for local database
}

//从服务端获取群组信息
std::vector<GroupInfo> Dealer::get_group_from_server() {
    //todo: call for the server
    auto v = client.call<std::vector<chatGroup_with_members> >("get_all_chatGroups");
//    std::cout<<v.size()<<std::endl;
    std::vector<GroupInfo> groups = Convert::cv_vgroup_to_client(v);
    std::cout << groups.size() << std::endl;
    for (auto &tmp:groups) {
        std::cout << tmp.getGroupId() << std::endl;
        for (auto &ss:tmp.getMemberId())
            std::cout << "   " << ss;
        std::cout << std::endl;
    }
    return groups;
}

//更新本地群组信息
void Dealer::update_local_group(const std::vector<GroupInfo> &group) {
    //todo: call for the local database
}

//从服务端获取消息信息
std::vector<MessageInfo> Dealer::get_message_from_server() {
    //todo: call for the server;
    auto xxx = client.call<vector<Message> >("get_all_message", userid);
    std::vector<MessageInfo> messages = Convert::cv_vmessage_to_client(xxx);
    std::cout << "handle:" << messages.size() << std::endl;

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
    return client.call<int>("create_package", userid, 0, packetname);
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
    bool op = client.call<bool>("change_name_of_package", userid, packet.getPacketId(), packet.getPacketName());
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

//todo:
void Dealer::server_delete_packet(const PacketInfo &packet) {

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
GroupInfo *Dealer::UI_create_group(const std::string &groupname, const std::vector<int> &memberids) {
    int id = ask_server_to_create_group(groupname, memberids);
    if (id == 0)
        return nullptr;
    GroupInfo *newgroup = add_group(GroupInfo(id, groupname, "", "", memberids));
    update_local_group(*newgroup);
    return newgroup;
}

//建群
GroupInfo *Dealer::UI_create_group(const std::string &groupname, const std::vector<UserInfo *> &members) {
    std::vector<int> memberids;
    for (auto &tmp:members) {
        memberids.push_back(tmp->getUserId());
    }
    int id = ask_server_to_create_group(groupname, memberids);
    if (id == 0)
        return nullptr;
    GroupInfo *newgroup = add_group(GroupInfo(id, groupname, "", "", memberids));
    update_local_group(*newgroup);
    return newgroup;
}

//告诉服务器要建群
int Dealer::ask_server_to_create_group(const std::string &name, const std::vector<int> &members) {
    return client.call<int>("create_chatGroup_and_invite_friends", name, members);
}

//更新本地数据群关系
void Dealer::update_local_group(const GroupInfo &group) {
    //todo: call for local database
}

//被拉进群
void Dealer::be_added_in_group(GroupInfo group) {
    GroupInfo *newgroup = add_group(group);
    update_local_group(group);
    //todo:
//    receiver->groupUpdate(newgroup);
}

//离开群
bool Dealer::leave_group(GroupInfo *group) {
    if (tell_server_to_leave_group(*group)) {
        return 0;
    } else {
        return 1;
    }
}

//本地删群
void Dealer::local_delete_group(const GroupInfo &group) {
    //todo: call local database
}

//告诉服务器退群
int Dealer::tell_server_to_leave_group(const GroupInfo &group) {
    int id = client.call<bool>("leave_group", userid, group.getGroupId());
    return 0;
}

//某人离开群
//void Dealer::someone_leave_group(const int &groupid, const int &userid) {
//    if (GroupMap.count(groupid) && UserMap.count(userid)) {
//        GroupMap[groupid]->delete_member(UserMap[userid]);
//        //todo: call UI
//    }
//}


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

void Dealer::someone_online(int id) {
    _mtx.lock();
    if (UserMap.count(id)) {
        UserInfo *user = UserMap[id];
        user->setStatus(1);
        _mtx.unlock();
        receiver->friendUpdate(user);
        //todo: call UI
    } else {
        _mtx.unlock();
    }
}

void Dealer::someone_offline(int id) {
    _mtx.lock();
    if (UserMap.count(id)) {
        UserInfo *user = UserMap[id];
        user->setStatus(0);
        _mtx.unlock();
        receiver->friendUpdate(user);
        //todo: call UI
    } else {
        _mtx.unlock();
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
    std::cout << "Find OK" << std::endl;
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
    auto xxx=client.call<userinfo>("get_info_by_uid", tmpmember);
    return Convert::cv_user_to_client(xxx);
}

//用nickname向服务器请求对方信息
UserInfo Dealer::find_user_from_server(const std::string &username) {
    std::cout << "query:" << username << std::endl;
    auto xxx=client.call<userinfo>("get_info_by_username", username);
    std::cout<<"after get"<<xxx.id<<std::endl;
    UserInfo user = Convert::cv_user_to_client(xxx);
    std::cout << user.getUserId() << std::endl;
    if (UserMap.count(user.getUserId())) {
        std::cerr << "some mistakes, try to find an existed user from server whose name is " << user.getUserName()
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
//    int op = client.call<int>("change_package", userid, user.getUserId(), user.getInPacket()->getPacketName());
}

void Dealer::update_friend(UserInfo user) {   //server_call
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

void Dealer::server_ask_to_add_friend(UserInfo user) {
    _mtx.lock();
    if (UserMap.count(user.getUserId())) {
        if (user.getPacket() > 0) {
            std::cerr << "does exist this friend" << std::endl;
        }
        _mtx.unlock();
    } else {
        UserInfo *newuser = add_user(user);
        _mtx.unlock();
        receiver->friendUpdate(newuser);
        //todo: call for UI to choose whether to accept
    }

}

void Dealer::UI_accept_add_friend(int userid, PacketInfo *packet) {
    UI_move_friend(UserMap[userid], packet);
}

void Dealer::tell_server_accept_friend(UserInfo newfriend) {
    int op = client.call<bool>("make_friend", userid, newfriend.getUserId());
}


void Dealer::friend_be_accepted(UserInfo user) {
    _mtx.lock();
    if (UserMap.count(user.getUserId())) {
        UI_move_friend(UserMap[user.getUserId()], PacketMap[user.getPacket()]);
        _mtx.unlock();
        receiver->friendUpdate(UserMap[user.getUserId()]);
    } else {
        UserInfo *tmp = add_user(user);
        _mtx.unlock();
        receiver->friendUpdate(tmp);
    }

    //todo: call UI
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

//todo:::
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
    bool op = client.call<bool>("delete_friend", userid, oldfriend->getUserId());
    local_delete_friend(*oldfriend);
    delete_friend(oldfriend);
}

//服务器请求删除好友
// todo:::::
void Dealer::server_delete_friend(UserInfo oldfriend) {
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
    int op = client.call<int>("send_message", userid, newmsg.getReceiverId(), newmsg.getContentKind(),
                              (newmsg.getType() == 2), newmsg.getContent());
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
    DateTime sendtime(local->tm_year + 1900, local->tm_mon + 1, local->tm_mday, local->tm_hour, local->tm_min,
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

void Dealer::receive_new_message(MessageInfo msg) {
    _mtx.lock();
    add_local_message(msg);
    MessageInfo *newmsg = cope_new_message(msg); //may exist bug here
    if (newmsg->getContentKind()>1)
    {
        std::vector<char> it=client.call<std::vector<char> >("read_file",newmsg->getContent());
        MyFile download;
        download.save_file(newmsg->getContent(),it);
    }
    _mtx.unlock();
    //todo:
    receiver->receiveMessage(newmsg);
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
    test.push_back(*(new MessageInfo(10001, 10002, "测试专用场地", 1, 1, 1, DateTime("2019-08-31 12:31:55"))));
    test.push_back(MessageInfo(10001, 10001, "test", 1, 2, 1, DateTime("2019-08-31 12:31:55")));
    test.push_back(MessageInfo(10002, 10001, "accepted", 1, 2, 1, DateTime("2019-08-31 12:32:05")));
    test.push_back(MessageInfo(10002, 10001, "蛤？", 1, 1, 1, DateTime("2019-08-31 11:32:05")));
    for (auto &tmp:test)
        std::cout << tmp.getCreateTime().getString() << std::endl;
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
    cout << messages.size() << endl;
    for (auto &tmp:messages)
        cout << tmp.getCreateTime().getString() << endl;
//    update_local_messages(messages);
//    messages = get_messages_from_local();
    for (auto &tmp:messages) {
        MessageInfo *tmpmsg = cope_new_message(tmp);
        cout << tmp.getCreateTime().getString() << endl;
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
    sleep(2);
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
            cout << "  " << msgs->getSender()->getNickName() << ": " << msgs->getContent() << "  "
                 << msgs->getCreateTime().getString() << endl;
        }
        cout << "--------------------------------------------------" << endl;
    }
}

/******************************Attention******************************/
//UI的会话消息需要调用我的函数，不能直接使用数据否则会话列表可能发生错误
/******************************Init******************************/
void Dealer::init(std::string sip) {
    serverip = sip;
}
/***********************************UI-Interface**************************************/

//登录
void Dealer::loginMethod(const std::string &username, const std::string &password,
                         std::function<void(std::vector<PacketInfo *> &, std::vector<GroupInfo *> &,
                                            std::vector<ChatInfo *> &)> success,
                         std::function<void(std::string)> fail) {

    _mtx.lock();

    client = FeverRPC::Client(serverip.c_str());
    ::Access_Key.username = username;
    ::Access_Key.password = password;
    ::Access_Key.ip = ip;
    uid = client.call<int>("login", username, password, ip);

    if (uid) {
        userid = uid;
        std::thread _t([=]() {
            FeverRPC::Client s2c(serverip.c_str());
            s2c.bind("login", CheckAccess);
            s2c.bind("friendQuest", FriendWantAdd);
            s2c.bind("friendConfirm", FriendConfirm);
            s2c.bind("userLogin", SomeoneOnline);
            s2c.bind("userLogout", SomeoneOffline);
            s2c.bind("groupAdd", GroupAdd);
            s2c.bind("newMessage", ReveiveMessage);
            s2c.s2c();
        });
        _t.detach();
        get_information_and_update();
//    test();
        success(PacketList, GroupList, ChatList);
        _mtx.unlock();
        std::cout << "ok" << std::endl;
    } else {
        _mtx.unlock();
        fail("不知道出了什么问题，反正就是登录失败了！");
    }
}


void
Dealer::getMyprofileMethod(std::function<void(UserInfo *)> getprofile, std::function<void(std::string)> error) {
    _mtx.lock();
    if (MyProfile.getUserId() != 0) {
        _mtx.unlock();
        getprofile(MyProfileCopy);
    } else {
        _mtx.unlock();
        error("还未获得个人信息");
    }
}

void Dealer::queryUserMethod(std::string username, std::function<void(UserInfo *)> success,
                             std::function<void(std::string)> fail) {
    _mtx.lock();
    UserInfo *user = add_user(username);
    if (user) {
        _mtx.unlock();
        success(user);
    } else {
        _mtx.unlock();
        fail("查无此人");
    }
}

void Dealer::addFriendMethod(int id, std::function<void(std::string)> success, std::function<void(std::string)> fail) {
    _mtx.lock();
    //todo:
    std::cout<<"add friend "<<UserMap.count(id)<<" "<<UserMap[id]->getPacket()<<std::endl;
    if (UserMap[id]->getPacket() == 0) {
        std::cout<<" addddd "<<id<<std::endl;

        bool op = client.call<bool>("request_friend", userid, id);
        std::cout<<" ok"<<std::endl;
        UI_add_friend(UserMap[id],1);
        _mtx.unlock();
        success("我觉得可以");
    } else {
        _mtx.unlock();
        fail("我觉得不行");
    }
}

void Dealer::agreefriendMethod(int id, std::function<void(UserInfo *)> success, std::function<void(std::string)> fail) {
    _mtx.lock();
    //todo:
    if ( UserMap[id]->getPacket() == 0) {
        bool op = client.call<bool>("make_friend", userid, id);
        UI_move_friend(add_user(id), 1);
        _mtx.unlock();
        success(UserMap[id]);
    } else {
        _mtx.unlock();
        fail("我觉得不行");
    }
}

void
Dealer::deleteFriendMethod(int id, std::function<void(std::string)> success, std::function<void(std::string)> fail) {
    _mtx.lock();
    //todo:
    UI_delete_friend(UserMap[id]);
    _mtx.unlock();
    success("我觉得可以");
}

void Dealer::moveToPacketMethod(UserInfo *user, PacketInfo *packet, std::function<void(std::string)> success,
                                std::function<void(std::string)> fail) {
    _mtx.lock();
    if (user->getInPacket() != packet) {
        UI_move_friend(user, packet);
        _mtx.unlock();
        success("可能可以");
    } else {
        _mtx.unlock();
        fail("这样不行");
    }
}

void
Dealer::addPacketMethod(std::string name, std::function<void(PacketInfo *)> success,
                        std::function<void(std::string)> fail) {
    _mtx.lock();
    PacketInfo *packet = UI_add_packet(name);
    _mtx.unlock();
    if (packet)
        success(packet);
    else
        fail("我觉得不行");
}

void Dealer::renamePacketMethod(std::string name, PacketInfo *packet, std::function<void(std::string)> success,
                                std::function<void(std::string)> fail) {
    _mtx.lock();
    if (UI_change_packetname(packet, name)) {
        _mtx.unlock();
        fail("这样不行");
    } else {
        _mtx.unlock();
        success("好像可以");
    }

}

void
Dealer::deletePacketMethod(PacketInfo *packet, std::function<void(std::string)> ok,
                           std::function<void(std::string)> fail) {
    _mtx.lock();
    if (UI_delete_packet(packet)) {
        _mtx.unlock();
        fail("这样不行");
    } else {
        _mtx.unlock();
        ok("好像可以");
    }
}

void Dealer::addGroupMethod(std::string name, std::vector<int> userList, std::function<void(GroupInfo *)> success,
                            std::function<void(std::string)> fail) {
    _mtx.lock();
    GroupInfo *group = UI_create_group(name, userList);
    _mtx.unlock();
    if (group == nullptr)
        fail("好像不行");
    else
        success(group);
}

void Dealer::exitGroupMethod(GroupInfo *group, std::function<void(std::string)> success,
                             std::function<void(std::string)> fail) {
    _mtx.lock();
    leave_group(group);
    _mtx.unlock();
    success("可能成功了");
}

MessageInfo *Dealer::newMessage(int type, std::string content, ChatInfo *chat) {
    tm *local;
    time_t t;
    t = time(NULL);
    local = localtime(&t);
    MessageInfo *tmp;
    DateTime sendtime(local->tm_year + 1900, local->tm_mon + 1, local->tm_mday, local->tm_hour, local->tm_min,
                      local->tm_sec);
    if (chat->getChatWith() == 1) {
        MessageInfo newmsg = MessageInfo(MyProfile.getUserId(), chat->getToUser()->getUserId(), content, 1, 1, type,
                                         sendtime);
        tmp = cope_new_message(newmsg);
        return tmp;
    } else if (chat->getChatWith() == 2) {
        MessageInfo newmsg = MessageInfo(MyProfile.getUserId(), chat->getToGroup()->getGroupId(), content, 1, 2,
                                         type,
                                         sendtime);
        tmp = cope_new_message(newmsg);
        return tmp;
    } else {
        MessageInfo newmsg = MessageInfo(MyProfile.getUserId(), chat->getToGroup()->getGroupId(), content, 1, 2,
                                         type,
                                         sendtime);
        tmp = cope_new_message(newmsg);
        return tmp;
    }
}

void Dealer::signinMethod(std::string username, std::string password, std::function<void(std::string)> success,
                          std::function<void(std::string)> fail) {
    _mtx.lock();
    client = FeverRPC::Client(serverip.c_str());
//    bool ismale=true;
    uid = client.call<int>("register", username, password, username, true);
    _mtx.unlock();
    if (uid) {
        success("注册成功");
    } else {
        fail("用户已被注册");
    }
}


void Dealer::sendMessageMethod(MessageInfo *msg, std::function<void(std::string)> success,
                               std::function<void(std::string)> fail) {
    _mtx.lock();
    if (msg->getContentKind()>1){
        MyFile loadfile(msg->getContent(),msg->getContentKind());
        int ok=client.call<int>("save_file",loadfile.getfilename(),loadfile.getvefile());
        sleep(0.1);
        std::cout<<"uploadfine"<<std::endl;
        msg->setContent(loadfile.getfilename());
        std::cout<<"set fine"<<std::endl;
    }
    std::cout<<"okokokok"<<std::endl;
    int result = send_message_to_server(*msg);
    std::cout<<"sdfasdf"<<std::endl;
    if (result) {
        msg->setMessageId(result);
        add_local_message(*msg);
        _mtx.unlock();
        success("好像可以");
    } else {
        msg->setStatus(0);
        add_local_message(*msg);
        _mtx.unlock();
        fail("这样不行");
    }
}



//void Dealer::updateMyInfoMethod(std::function<void(std::string)> success, std::function<void(std::string)> fail) {
//    client.call<int>("update_info")
//}


/**************************************Thread***************************************/

/***************************************SERVER***************************************/

void Dealer::receiveMessage(MessageInfo msg) {
    std::cout << msg.getContent() << std::endl;
    std::thread t(std::bind(&Dealer::receive_new_message, this, msg));
    t.detach();
}

void Dealer::friendWanttoAdd(UserInfo user) {
    std::thread t(std::bind(&Dealer::server_ask_to_add_friend, this, user));
    t.detach();
}

void Dealer::friendConfirm(UserInfo user) {
    std::thread t(std::bind(&Dealer::friend_be_accepted, this, user));
    t.detach();
}

void Dealer::userLogin(int id) {
    std::thread t(std::bind(&Dealer::someone_online, this, id));
    t.detach();
}

void Dealer::userLogout(int id) {
    std::thread t(std::bind(&Dealer::someone_offline, this, id));
    t.detach();
}

void Dealer::groupAdd(GroupInfo group) {
    std::thread t(std::bind(&Dealer::be_added_in_group, this, group));
    t.detach();
}

/**************************************************thread ********************************************************/
void Dealer::queryUser(std::string username, std::function<void(UserInfo *)> success,
                       std::function<void(std::string)> fail) {
    std::thread t(std::bind(&Dealer::queryUserMethod, this, username, success, fail));
    t.detach();
}

void Dealer::addFriend(int id, std::function<void(std::string)> success, std::function<void(std::string)> fail) {
    std::thread t(std::bind(&Dealer::addFriendMethod, this, id, success, fail));
    t.detach();
}

void Dealer::agreefriend(int id, std::function<void(UserInfo *)> success, std::function<void(std::string)> fail) {
    std::thread t(std::bind(&Dealer::agreefriendMethod, this, id, success, fail));
    t.detach();
}

void Dealer::deleteFriend(int id, std::function<void(std::string)> success, std::function<void(std::string)> fail) {
    std::thread t(std::bind(&Dealer::deleteFriendMethod, this, id, success, fail));
    t.detach();
}

void Dealer::moveToPacket(UserInfo *user, PacketInfo *packet, std::function<void(std::string)> success,
                          std::function<void(std::string)> fail) {
    std::thread t(std::bind(&Dealer::moveToPacketMethod, this, user, packet, success, fail));
    t.detach();
}

void
Dealer::addPacket(std::string name, std::function<void(PacketInfo *)> success, std::function<void(std::string)> fail) {
    std::thread t(std::bind(&Dealer::addPacketMethod, this, name, success, fail));
    t.detach();
}

void Dealer::renamePacket(std::string name, PacketInfo *packet, std::function<void(std::string)> success,
                          std::function<void(std::string)> fail) {
    std::thread t(std::bind(&Dealer::renamePacketMethod, this, name, packet, success, fail));
    t.detach();
}

void
Dealer::deletePacket(PacketInfo *packet, std::function<void(std::string)> ok, std::function<void(std::string)> fail) {
    std::thread t(std::bind(&Dealer::deletePacketMethod, this, packet, ok, fail));
    t.detach();
}

void Dealer::addGroup(std::string name, std::vector<int> userList, std::function<void(GroupInfo *)> success,
                      std::function<void(std::string)> fail) {
    std::thread t(std::bind(&Dealer::addGroupMethod, this, name, userList, success, fail));
    t.detach();
}

void
Dealer::exitGroup(GroupInfo *group, std::function<void(std::string)> success, std::function<void(std::string)> fail) {
    std::thread t(std::bind(&Dealer::exitGroupMethod, this, group, success, fail));
    t.detach();
}

void
Dealer::sendMessage(MessageInfo *msg, std::function<void(std::string)> success, std::function<void(std::string)> fail) {
    std::thread t(std::bind(&Dealer::sendMessageMethod, this, msg, success, fail));
    t.detach();
}

//void Dealer::updateMyInfo(std::function<void(std::string)> success, std::function<void(std::string)> fail) {
//    std::thread t(std::bind(&Dealer::updateMyInfoMethod, success, fail));
//    t.detach();
//}

void Dealer::login(const std::string &username, const std::string &password,
                   std::function<void(std::vector<PacketInfo *> &, std::vector<GroupInfo *> &,
                                      std::vector<ChatInfo *> &)> success, std::function<void(std::string)> fail) {
    std::thread t(std::bind(&Dealer::loginMethod, this, username, password, success, fail));
    t.detach();
}

void
Dealer::getMyprofile(std::function<void(UserInfo *)> getprofile, std::function<void(std::string)> error) {
    std::thread t(std::bind(&Dealer::getMyprofileMethod, this, getprofile, error));
    t.detach();
}

ChatInfo *
Dealer::chatWith(UserInfo *user) {
    return get_chat(user);
}

ChatInfo *
Dealer::chatWith(GroupInfo *group) {
    return get_chat(group);
}


















