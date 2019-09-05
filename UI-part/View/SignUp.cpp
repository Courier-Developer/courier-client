//
// Created by ervinxie on 8/31/19.
//

#include <iostream>
#include "implement.h"

SignUp::SignUp(Glib::RefPtr<Gtk::Application> app) {
    get_style_context()->add_class("SignUp");
    this->app = app;

    set_title("Sign Up at Courier");
    set_position(Gtk::WIN_POS_CENTER);
    set_size_request(800, 800);


    vbox.pack_end(infoGrid, Gtk::PACK_SHRINK);
    vbox.pack_start(welcomeImage);
    welcomeImage.set(PixMan::getIcon("welcome", 300));

    add(vbox);


    infoGrid.set_border_width(10);
    infoGrid.set_halign(Gtk::ALIGN_CENTER);
    infoGrid.set_valign(Gtk::ALIGN_CENTER);
    infoGrid.set_row_spacing(2);
    infoGrid.set_column_spacing(2);

    usernameLabel.set_text("User Name");
    username.set_placeholder_text("Must Be Unique");
    username.set_icon_from_pixbuf(PixMan::getIcon("user", 15));
//    infoGrid.attach(usernameLabel, 0, 0, 1, 1);
    infoGrid.attach(username, 0, 0, 2, 1);

    passwordLabel.set_text("Password");
    password.set_placeholder_text("Decide Password");
    password.set_visibility(false);
    password.set_invisible_char(Glib::ustring("·").at(0));
    password.set_icon_from_pixbuf(PixMan::getIcon("lock", 15));
//    infoGrid.attach(passwordLabel, 0, 1, 1, 1);
    infoGrid.attach(password, 0, 1, 2, 1);


    rePasswordLabel.set_text("Repeat Password");
    rePassword.set_placeholder_text("Repeat Password");
    rePassword.set_visibility(false);
    rePassword.set_invisible_char(Glib::ustring("·").at(0));
    rePassword.set_icon_from_pixbuf(PixMan::getIcon("lock", 15));
//    infoGrid.attach(rePasswordLabel, 0, 2, 1, 1);
    infoGrid.attach(rePassword, 0, 2, 2, 1);


    showPassword.set_label("Show Password");
    showPassword.set_active(false);
    showPassword.set_halign(Gtk::ALIGN_START);
    showPassword.signal_toggled().connect([this] {
        if (this->showPassword.get_active()) {
            password.set_visibility(true);
            rePassword.set_visibility(true);

        } else {
            password.set_visibility(false);
            rePassword.set_visibility(false);
        }
    });
    infoGrid.attach(showPassword, 0, 3, 2, 1);

    signUpBt.set_label("Sign Up");
    signUpBt.signal_clicked().connect([this] {
        dealer.signinMethod(this->username.get_text(), this->password.get_text(), [&](std::string s) {
            std::cout << s << std::endl;
        }, [&](std::string f) {
            std::cout << f << std::endl;

        });

    });
    infoGrid.attach(signUpBt, 0, 4, 2, 1);

    logInBt.set_label("Back to Log In");
    logInBt.signal_clicked().connect([this] {
        LogIn *logIn = new LogIn(this->app);
        this->app->add_window(*logIn);
        logIn->show();

        this->hide();
        this->app->remove_window(*this);
    });
    infoGrid.attach(logInBt, 0, 5, 2, 1);


    show_all_children();
}

SignUp::~SignUp() {

}
