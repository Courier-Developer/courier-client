//
// Created by ervinxie on 8/31/19.
//

#ifndef COURIER_CLIENT_SIGNUP_H
#define COURIER_CLIENT_SIGNUP_H

#include <gtkmm.h>
#include "ChatWindow/ChatWindow.h"
#include "ChatWindow/Chatting.h"
#include "ChatWindow/ChatList.h"
#include "ContactWindow/ContactWindow.h"
#include "OtherWindow/OtherWindow.h"

class SignUp :public Gtk::Window{
public:
    SignUp(Glib::RefPtr<Gtk::Application> app);
    virtual ~SignUp();

protected:
    Glib::RefPtr<Gtk::Application> app;
    Gtk::Grid grid;

    Gtk::Entry username,password,rePassword;
    Gtk::Label usernameLabel,passwordLabel,rePasswordLabel;

    Gtk::Button signUpBt,logInBt;
    Gtk::CheckButton showPassword;


};


#endif //COURIER_CLIENT_SIGNUP_H
