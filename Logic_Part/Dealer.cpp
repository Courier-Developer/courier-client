//
// Created by 孙璋亮 on 2019-08-31.
//

#include <iostream>
#include "Dealer.h"
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
    if (tmpmsg->getType() == 1) {
        unsigned int chatto = tmpmsg->getSenderId();
        if (chatto == MyProfile.getUserId())
            chatto = tmpmsg->getReceiverId();
        //there maybe some bug
        if (UserMap.count(chatto) == 0) {
            std::cerr << "there exists a message can't find the person chat with" << std::endl;
        }
        UserInfo *touser = UserMap[chatto];
        ChatInfo *chat = get_chat(touser);
        chat->AddMessage(tmpmsg);
    } else {
        if (tmpmsg->getType() == 2) {
            if (GroupMap.count(tmpmsg->getReceiverId()) == 0) {
                std::cerr << "there exists a message can't find the group chat in" << std::endl;
            }
            GroupInfo *togroup = GroupMap[tmpmsg->getReceiverId()];
            ChatInfo *chat = get_chat(togroup);
            chat->AddMessage(tmpmsg);
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


int Dealer::ask_server_to_add_packet(const std::string &packetname) {
    //todo: ask server to add packet
    return packetnum++;
}

void Dealer::UI_add_packet(const std::string &packetname) {
    int packetid = ask_server_to_add_packet(packetname);
    if (packetid) {
        PacketInfo *newpacket = add_packet(packetid, packetname);
    } else {
        std::cerr << "create packet Error" << std::endl;
    }
}

void Dealer::local_update_packet(const PacketInfo &packet) {
    //todo: call for database 有则修改，无则添加
}

void Dealer::server_update_packet(const PacketInfo &packet) {
    //todo: call for server 有则修改，无则添加
}

void Dealer::UI_change_packetname(PacketInfo *packet, const std::string &name) {
    if (packet->getPacketId() > 0) {
        packet->setPacketName(name);
        local_update_packet(*packet);
        server_update_packet(*packet);
    } else {
        std::cerr << "try to rename <0 packet" << std::endl;
    }
}

void Dealer::UI_delete_packet(PacketInfo *packet) {
    if (packet->getUsers()->size()) {
        std::cerr << "try to delete a packet with friend" << std::endl;
    } else {
        if (packet->getPacketId() < 2) {
            std::cerr << "try to delete necessary packet" << std::endl;
        } else {
            local_delete_packet(*packet);
            server_delete_packet(*packet);
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
// todo: 需要完善添加群组
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


/*************************************添加好友或移动好友分组或搜索好友*********************************/

//用id添加新用户
UserInfo *Dealer::add_user(const unsigned int &tmpmember) {
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
UserInfo Dealer::find_user_from_server(const unsigned int &tmpmember) {
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
    UserMap[tmp->getUserId()]=tmp;
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

void Dealer::UI_search_user(const unsigned int &id) {
    UserInfo *tmp = add_user(id);
}



/*************************************删除好友**********************************/

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

void Dealer::delete_friend(UserInfo *oldfriend) {
    PacketInfo *oldpacket = oldfriend->getInPacket();
    oldpacket->DeleteMember(oldfriend);
    PacketInfo *stranger = get_packet_from_id(0);
    stranger->AddUser(oldfriend);
    oldfriend->setInPacket(stranger);
}


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

void Dealer::server_delete_friend(const UserInfo &oldfriend) {
    local_delete_friend(oldfriend);
    delete_friend(oldfriend);
    //todo: call for UI
}

void Dealer::local_delete_friend(const UserInfo &oldfriend) {
    //todo: call for local database
    return;
}

/*********************************发送消息***********************************/
void Dealer::UI_send_message(const std::string &content, ChatInfo *chat) {
    MessageInfo *newmsg = send_message(content, chat);
}

//获得messageid
int Dealer::send_message_to_server(const MessageInfo &newmsg) {
    //todo: call for server
    return 0;
}

void Dealer::add_local_message(const MessageInfo &newmsg) {
    //todo: update_local_message
}

MessageInfo *Dealer::send_message(const std::string &content, ChatInfo *chat) {
    tm *local;
    time_t t;
    t = time(NULL);
    local = localtime(&t);
    MessageInfo *tmp;
    DateTime sendtime(local->tm_year, local->tm_mon, local->tm_mday, local->tm_hour, local->tm_min, local->tm_sec);
    if (chat->getChatWith() == 1) {
        MessageInfo newmsg = MessageInfo(MyProfile.getUserId(), chat->getToUser()->getUserId(), content, 1, 1, 1,
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
            MessageInfo newmsg = MessageInfo(MyProfile.getUserId(), chat->getToGroup()->getGroupId(), content, 1, 2, 1,
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

void Dealer::server_ask_to_add_friend(const UserInfo user) {
    if (UserMap.count(user.getUserId())) {
        if (user.getPacket() > 0) {
            std::cerr << "does exist this friend" << std::endl;
        }
    }else{
        UserInfo *newuser=add_user(user);
        //todo: call for UI to choose whether to accept
    }
}

/******************************Attention******************************/
//UI的会话消息需要调用我的函数，不能直接使用数据否则会话列表可能发生错误

