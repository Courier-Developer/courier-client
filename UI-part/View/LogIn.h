//
// Created by ervinxie on 8/28/19.
//

#ifndef GTKMM_LOGIN_H
#define GTKMM_LOGIN_H


#include <gtkmm.h>
#include "MainWindow.h"

class LogIn :public Gtk::Window{
public:
    LogIn();
    virtual ~LogIn();

    Glib::RefPtr<Gtk::Application>* app;

protected:

    void on_login();
    void on_signin();



    Gtk::Grid grid;

    Gtk::Entry username,password;
    Gtk::Label usernameLable,passwordLable;


    Gtk::Button logInBt;
    Gtk::Button signInBt;

};


#endif //GTKMM_LOGIN_H
