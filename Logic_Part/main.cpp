#include "Dealer.h"
Dealer dealer;
int main()
{
    dealer.test();
    dealer.ShowTestUserInfo();
    dealer.ShowTestPacketInfo();
    dealer.ShowTestGroupInfo();
    dealer.ShowTestChatInfo();
    dealer.UI_send_message("fuck",dealer.get_chat(dealer.UserMap[10002]));
    dealer.ShowTestChatInfo();
    return 0;
}