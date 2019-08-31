#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "class/UserInfo.h"
#include "class/MessageInfo.h"

using std::vector;
std::map<unsigned int, UserInfo *> AllUser;
std::vector<PacketInfo> AllPacket;
std::vector<GroupInfo> AllGroup;


int main() {
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
