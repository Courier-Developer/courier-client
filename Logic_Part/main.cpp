#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "class/UserInfo.h"
#include "class/GroupInfo.h"
#include "class/MessageInfo.h"
#include "class/PacketInfo.h"
#include "class/ChatInfo.h"

using std::vector;
std::map<unsigned int, UserInfo *> AllUser;
std::vector<PacketInfo> AllPacket;
std::vector<GroupInfo> AllGroup;
std::map<int,PacketInfo *> PacketMap;

int main() {

//    AllPacket=
//    for (auto & tmp:AllPacket)
//    {
//    }
    //todo: achieve the table of all available User
    vector<UserInfo> gg;
    //todo: call for the local database
    for (auto &tmp:gg) {
        UserInfo *temp=new UserInfo(tmp);
        AllUser[tmp.getUserId()]=temp;
    }
    //todo:
//    AllPacket=





    return 0;
}
