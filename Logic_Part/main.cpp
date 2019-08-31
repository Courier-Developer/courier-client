#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "class/UserInfo.h"
#include "class/GroupInfo.h"
#include "class/MessageInfo.h"
#include "class/PacketInfo.h"
#include "class/ChatInfo.h"
#include <functional>

extern std::map<unsigned int, UserInfo *> AllUser;
extern std::vector<PacketInfo *> AllPacket;
extern std::vector<GroupInfo *> AllGroup;
extern std::map<int, PacketInfo *> PacketMap;
extern std::map<int,GroupInfo *> GroupMap;
extern UserInfo MyProfile;
extern UserInfo ChatTo;

void init() {
    AllPacket.clear();
    AllUser.clear();
    AllGroup.clear();
    PacketMap.clear();
    GroupMap.clear();
}


void LoginInit()
{

    {
        //todo: requset from server
        UserInfo myprofile;
        //todo: update the local server
        ChatTo=MyProfile=myprofile;
    }
    //todo: request the information from server
    {
        std::vector<PacketInfo> allpackets;
        //todo: update the local database
        for (auto &tmp:allpackets) {
            PacketInfo *tmppacket=new PacketInfo(tmp);
            PacketMap[tmppacket->getPacketId()]=tmppacket;
            AllPacket.push_back(tmppacket);
        }
    }
    //todo:request the information from server
    {
        std::vector<UserInfo> users;
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
        //todo: get information from server
        std::vector<GroupInfo> groups;
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

    }
}


void Login(std::string username, std::string password,std::function<void(std::vector<GroupInfo *>,
        std::vector<PacketInfo *>,std::vector<ChatInfo *>)>,std::function<void(std::string)>){
    //todo: call for the UI
}

void Signin(std::string username,std::string password,std::string nickname,std::function<void()>,std::function<void(std::string)>){

}


//void login(std::string username, std::string password,)
