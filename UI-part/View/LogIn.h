//
// Created by ervinxie on 8/28/19.
//

#ifndef GTKMM_LOGIN_H
#define GTKMM_LOGIN_H


#include <gtkmm.h>
#include "OtherWindow/OtherWindow.h"

class LogIn : public Gtk::Window {
public:
    LogIn(Glib::RefPtr<Gtk::Application> app);

    virtual ~LogIn();

    MainWindow *mainWindow;

    Glib::Dispatcher dispatcher;
protected:
    Glib::RefPtr<Gtk::Application> app;
    Gtk::VBox vbox;
    Gtk::Image welcomeImage;
    Gtk::Grid infoGrid;


    Gtk::Entry username, password;
    Gtk::Label usernameLabel, passwordLabel;

    Gtk::CheckButton showPassword;
    Gtk::Button signUpBt;
    Gtk::Button logInBt;

    Gtk::Spinner spinner;

};


#endif //GTKMM_LOGIN_H
