//
// Created by ervinxie on 8/28/19.
//

#ifndef GTKMM_LOGIN_H
#define GTKMM_LOGIN_H


#include <gtkmm.h>
#include "OtherWindow/OtherWindow.h"
Receiver* receiver;
class LogIn : public Gtk::Window {
public:
    LogIn(Glib::RefPtr<Gtk::Application> app);

    virtual ~LogIn();


protected:
    Glib::RefPtr<Gtk::Application> app;

    Gtk::Grid grid;

    Gtk::Entry username, password;
    Gtk::Label usernameLabel, passwordLabel;

    Gtk::CheckButton showPassword;
    Gtk::Button signUpBt;
    Gtk::Button logInBt;

};


#endif //GTKMM_LOGIN_H
