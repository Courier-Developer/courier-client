#include<gtkmm-3.0/gtkmm.h>

#include "View/implement.h"

#include <zconf.h>
#include "Convert.h"

Dealer dealer;
ThemeManage* themeManage;

Login Access_Key;

std::string serverip="10.194.151.197";
int ReveiveMessage(Message msg)
{
    MessageInfo mess=Convert::cv_message_to_client(msg);
    dealer.receiveMessage(mess);
    return 0;
}

int FriendWantAdd(Friend fri)
{
    UserInfo newfriend=Convert::cv_friend_to_client(fri);
    dealer.friendWanttoAdd(newfriend);
    return 0;
}

int FriendConfirm(Friend fri)
{
    UserInfo newfriend=Convert::cv_friend_to_client(fri);
    dealer.friendConfirm(newfriend);
    return 0;
}

int SomeoneOnline(int id)
{
    dealer.userLogin(id);
    return 0;
}

int SomeoneOffline(int id)
{
    dealer.userLogout(id);
    return 0;
}

int GroupAdd(chatGroup_with_members group)
{
    GroupInfo newgroup=Convert::cv_group_to_client(group);
    dealer.groupAdd(newgroup);
    return 0;
}

Login CheckAccess()
{
    return Access_Key;
}


int main(int argc, char *argv[])
{
    dealer.init(serverip);
    std::thread _t([](){
        FeverRPC::Client s2c(serverip.c_str());
        s2c.bind("login",CheckAccess);
        s2c.bind("friendQuest",FriendWantAdd);
        s2c.bind("friendConfirm",FriendConfirm);
        s2c.bind("userLogin",SomeoneOnline);
        s2c.bind("userLogout",SomeoneOffline);
        s2c.bind("groupAdd",GroupAdd);
        s2c.bind("newMessage",ReveiveMessage);
        s2c.s2c();
    });
    _t.detach();


    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv,"com.courier");
    LogIn logIn(app);

    themeManage = new ThemeManage;


    return app->run(logIn);
}