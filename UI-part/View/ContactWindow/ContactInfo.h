//
// Created by ervinxie on 8/28/19.
//

#ifndef GTKMM_CONTACTINFO_H
#define GTKMM_CONTACTINFO_H


#include <gtkmm.h>
#include "../../../Logic_Part/class/UserInfo.h"

class ContactInfo : public Gtk::Grid{
public:
    ContactInfo();
    ContactInfo(UserInfo* userInfo);
    virtual ~ContactInfo();
    void ChangeUser(UserInfo* newUser);

protected:


    Glib::RefPtr<Gdk::Pixbuf> avatar;
    Gtk::Label nickName;
};


#endif //GTKMM_CONTACTINFO_H
