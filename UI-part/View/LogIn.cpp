//
// Created by ervinxie on 8/28/19.
//

#include <iostream>
#include "implement.h"
LogIn::LogIn(Glib::RefPtr<Gtk::Application> app) {
    this->app = app;

    set_title("Welcome to Courier");
    set_position(Gtk::WIN_POS_CENTER);
    set_size_request(300, 50);


    grid.set_border_width(10);
    grid.set_halign(Gtk::ALIGN_CENTER);
    grid.set_valign(Gtk::ALIGN_CENTER);
    grid.set_row_spacing(2);
    grid.set_column_spacing(2);
    add(grid);

    usernameLabel.set_text("User Name");
    grid.attach(usernameLabel, 0, 0, 1, 1);

    grid.attach(username, 1, 0, 1, 1);

    passwordLabel.set_text("Password");
    grid.attach(passwordLabel, 0, 1, 1, 1);
    grid.attach(password, 1, 1, 1, 1);
    password.set_visibility(false);
    password.set_invisible_char('*');

    showPassword.set_label("Show Password");
    showPassword.set_active(false);
    showPassword.set_halign(Gtk::ALIGN_END);
    showPassword.signal_toggled().connect([this] {
        if (this->showPassword.get_active()) {
            password.set_visibility(true);
        } else {
            password.set_visibility(false);
        }
    });
    grid.attach(showPassword, 0, 2, 2, 1);

    signUpBt.set_label("Sign Up");
    signUpBt.signal_clicked().connect([this] {
        SignUp *signUp = new SignUp(this->app);
        this->app->add_window(*signUp);
        signUp->show();
        this->hide();
        this->app->remove_window(*this);
    });
    grid.attach(signUpBt, 0, 3, 2, 1);

    logInBt.set_label("Log In");
    logInBt.signal_clicked().connect([this] {

        MainWindow *mainWindow = new MainWindow(this->app);
        this->app->add_window(*mainWindow);
        mainWindow->show();
        this->hide();
        this->app->remove_window(*this);
    });
    grid.attach(logInBt, 0, 4, 2, 1);


    show_all_children();
}

LogIn::~LogIn() {}
