//
// Created by ervinxie on 8/28/19.
//

#ifndef GTKMM_CONTACTINFO_H
#define GTKMM_CONTACTINFO_H


#include "../ChatWindow/ChatWindow.h"
#include "../../../Logic_Part/UI-Interface/UserInfo.h"

class ContactInfo : public Gtk::Grid{
public:
    ContactInfo(int avatarSize = 64);
    ContactInfo(UserInfo* userInfo,int avatarSize = 64);
    virtual ~ContactInfo();
    void ChangeUser(UserInfo* newUser);


protected:
    UserInfo* user;
    int avatarSize=64;
    Glib::RefPtr<Gdk::Pixbuf> avatar;
    Gtk::Label nickName;
};


#endif //GTKMM_CONTACTINFO_H
