#include "Dealer.h"
#include <thread>
#include <iostream>
//#include "feverrpc/feverrpc.hpp"
Dealer dealer;
//Login Access_Key;

//int receiveMsg(Mess)
int main()
{
    dealer.test();
//    cout<<dealer.ip<<endl;
    dealer.ShowTestUserInfo();
    dealer.ShowTestPacketInfo();
    dealer.ShowTestGroupInfo();
    dealer.ShowTestChatInfo();
//    dealer.UI_send_message("fuck",dealer.get_chat(dealer.UserMap[10002]));
    dealer.ShowTestChatInfo();
    return 0;
}