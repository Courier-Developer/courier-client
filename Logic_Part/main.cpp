#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "UI-Interface/UserInfo.h"
#include "UI-Interface/GroupInfo.h"
#include "UI-Interface/MessageInfo.h"
#include "UI-Interface/PacketInfo.h"
#include "UI-Interface/ChatInfo.h"
#include "UI-Interface/predeclare.h"
#include <functional>
#include <fstream>

//extern std::map<unsigned int, UserInfo *> AllUser;
//extern std::vector<PacketInfo *> AllPacket;
//extern std::vector<GroupInfo *> AllGroup;
//extern std::map<int, PacketInfo *> PacketMap;
//extern std::map<int,GroupInfo *> GroupMap;
//extern UserInfo *MyProfile;
//extern UserInfo *ChatTo;


std::map<unsigned int, UserInfo *> AllUser;
std::vector<PacketInfo *> AllPacket;
std::vector<GroupInfo *> AllGroup;
std::map<int, PacketInfo *> PacketMap;
std::map<int, GroupInfo *> GroupMap;
std::vector<ChatInfo *> AllChat;

UserInfo *MyProfile;
UserInfo *ChatTo;

UserInfo *getMyInfo() {
    return MyProfile;
}

std::vector<PacketInfo *> &getAllPacket() {
    return AllPacket;
}

std::vector<GroupInfo *> &getAllGroup() {
    return AllGroup;
}

void AddChat(ChatInfo *newchat){
    AllChat.push_back(newchat);
}

std::vector<ChatInfo *> &getAllChat(){
    return AllChat;
}

void init() {
    AllPacket.clear();
    AllUser.clear();
    AllGroup.clear();
    PacketMap.clear();
    GroupMap.clear();
}

using  std::cin,std::cout,std::string,std::map,std::endl;
void LoginInit()
{

//    {
        //todo: requset from server
//        freopen("/Users/ironhead/CLionProjects/courier-client/Logic_Part/test/pac")
        UserInfo myprofile;

//        AllUser[temp->getUserId()] = temp;
//        //todo: update the local server
//        ChatTo=MyProfile=temp;
//    }
    //todo: request the information from server
    {
        freopen("/Users/ironhead/CLionProjects/courier-client/Logic_Part/test/packettest","r",stdin);
        string name;
        int id;
        std::vector<PacketInfo> allpackets;
        while (cin>>name>>id)
        {
            allpackets.push_back(PacketInfo(name,id));
//            cout<<"fuck"<<endl;
        }

        //todo: update the local database
        for (auto &tmp:allpackets) {
            PacketInfo *tmppacket=new PacketInfo(tmp);
            PacketMap[tmppacket->getPacketId()]=tmppacket;
            AllPacket.push_back(tmppacket);
        }
    }
    //todo:request the information from server
    {
        freopen("/Users/ironhead/CLionProjects/courier-client/Logic_Part/test/usertest","r",stdin);
        std::vector<UserInfo> users;
        int id,s,p;
        string username,nickname,signature,avator;
        while(cin>>id>>username>>nickname>>signature>>avator>>s>>p)
        {
            users.push_back(UserInfo(id,username,nickname,signature,avator,s,p));
        }
        //todo:update the local database
        for (auto &tmp:users) {
            UserInfo *temp = new UserInfo(tmp);
            AllUser[tmp.getUserId()] = temp;
            PacketInfo *inpacket = PacketMap[temp->getPacket()];
            temp->setInPacket(inpacket);
            inpacket->AddUser(temp);
        }
    }
    {
        freopen("/Users/ironhead/CLionProjects/courier-client/Logic_Part/test/grouptest","r",stdin);
        //todo: get information from server
        int id,num;
        string name,notice,avator;
        std::vector<GroupInfo> groups;
        while (cin>>id>>name>>avator>>notice>>num)
        {
//            cout<<"??"<<endl;
            std::vector<unsigned int> pp;
            while (num--){
                int tmp;
                cin>>tmp;
                pp.push_back(tmp);
            }
            groups.push_back(GroupInfo(id,name,avator,notice,pp));
        }
        //todo: update the local database
        for (auto &tmp:groups) {
                GroupInfo *tmpgroup=new GroupInfo(tmp);
                AllGroup.push_back(tmpgroup);
                GroupMap[tmpgroup->getGroupId()]=tmpgroup;
                for (auto &tmpmem:tmpgroup->getMemberId()){
                    UserInfo *mem=AllUser[tmpmem];
                    mem->setInGroup(tmpgroup);
                    tmpgroup->AddUser(mem);
            }
        }
    }

    {
        //todo: get information form local database
        freopen("/Users/ironhead/CLionProjects/courier-client/Logic_Part/test/messagetest","r",stdin);
        int id,sta,to,type,ye,mon,dd,hh,mm,ss,toid;
        string content;
        std::vector<MessageInfo> messages;
        while (cin>>id>>toid>>content>>sta>>to>>type>>ye>>mon>>dd>>hh>>mm>>ss)
            messages.push_back(MessageInfo(id,toid,content,sta,to,type,DateTime(ye,mon,dd,hh,mm,ss)));
        for (auto &tmp: messages)
        {
            MessageInfo * tmpmsg=new MessageInfo(tmp);
            if (tmpmsg->getType()==1){
                unsigned int chatto=tmpmsg->getSenderId();
                if (chatto==MyProfile->getUserId())
                    chatto=tmpmsg->getReceiverId();
                UserInfo *touser=AllUser[chatto];
                ChatInfo *chat=touser->getChat();
                chat->AddMessage(tmpmsg);
            }else{
                if (tmp.getType()==2){
                    GroupInfo *togroup=GroupMap[tmpmsg->getReceiverId()];
                    ChatInfo *chat=togroup->getChat();
                    chat->AddMessage(tmpmsg);
                }
            }
        }
    }

}


void Login(std::string username, std::string password,std::function<void(std::vector<GroupInfo *>,
        std::vector<PacketInfo *>,std::vector<ChatInfo *>)>,std::function<void(std::string)>){
    //todo: call for the UI
}

void Signin(std::string username,std::string password,std::string nickname,std::function<void()>,std::function<void(std::string)>){

}

int main()
{
    LoginInit();
    for (auto &tmp:AllGroup)
        cout<<tmp->getNickName()<<std::endl;
//    for (auto &tmp:AllPacket)
//        cout<<tmp->getName()<<std::endl;
    for (auto &tmp:AllChat)
        cout<<tmp->getChatWith()<<std::endl;
//    freopen("/Logic_Part/test/grouptest","r",stdin);
//    string tmp;
//    while (cin>>tmp)
//    {
//        cout<<tmp<<endl;
//    }
    return 0;
}

//void login(std::string username, std::string password,)
