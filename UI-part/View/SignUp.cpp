//
// Created by ervinxie on 8/31/19.
//

#include <iostream>
#include "SignUp.h"
#include "LogIn.h"
SignUp::SignUp(Glib::RefPtr<Gtk::Application> app) {
    this->app = app;

    set_title("Sign Up at Courier");
    set_position(Gtk::WIN_POS_CENTER);
    set_size_request(300, 50);

    add(grid);
    grid.set_border_width(10);
    grid.set_halign(Gtk::ALIGN_CENTER);
    grid.set_valign(Gtk::ALIGN_CENTER);
    grid.set_row_spacing(2);
    grid.set_column_spacing(2);

    usernameLabel.set_text("User Name");
    username.set_placeholder_text("Must Be Unique");
    grid.attach(usernameLabel, 0, 0, 1, 1);
    grid.attach(username, 1, 0, 1, 1);

    passwordLabel.set_text("Password");
    password.set_placeholder_text("Decide Password");
    password.set_visibility(false);
    password.set_invisible_char('*');
    grid.attach(passwordLabel, 0, 1, 1, 1);
    grid.attach(password, 1, 1, 1, 1);


    rePasswordLabel.set_text("Repeat Password");
    rePassword.set_placeholder_text("Repeat Password");
    rePassword.set_visibility(false);
    rePassword.set_invisible_char('*');
    grid.attach(rePasswordLabel, 0, 2, 1, 1);
    grid.attach(rePassword, 1, 2, 1, 1);


    showPassword.set_label("Show Password");
    showPassword.set_active(false);
    showPassword.set_halign(Gtk::ALIGN_END);
    showPassword.signal_toggled().connect([this] {
        if (this->showPassword.get_active()) {
            password.set_visibility(true);
            rePassword.set_visibility(true);

        } else {
            password.set_visibility(false);
            rePassword.set_visibility(false);
        }
    });
    grid.attach(showPassword, 1, 3, 1, 1);

    signUpBt.set_label("Sign Up");
    grid.attach(signUpBt, 0, 4, 2, 1);

    logInBt.set_label("Back to Log In");
    logInBt.signal_clicked().connect([this]{
        LogIn* logIn = new LogIn(this->app);
        this->app->add_window(*logIn);
        logIn->show();

        this->hide();
        this->app->remove_window(*this);
    });
    grid.attach(logInBt, 0, 5, 2, 1);


    show_all_children();
}

SignUp::~SignUp() {

}
