//
// Created by ervinxie on 8/28/19.
//

#include <iostream>
#include "implement.h"

Receiver *receiver;

LogIn::LogIn(Glib::RefPtr<Gtk::Application> app) {
    get_style_context()->add_class("LogIn");

    this->app = app;

    set_title("Welcome to Courier");
    set_position(Gtk::WIN_POS_CENTER);
    set_size_request(400, 400);


    add(vbox);
    vbox.pack_end(infoGrid, Gtk::PACK_SHRINK);
    vbox.pack_start(welcomeImage);
    vbox.pack_start(spinner, Gtk::PACK_SHRINK);
    welcomeImage.set(PixMan::getIcon("welcome", 300));


    infoGrid.set_border_width(10);
    infoGrid.set_halign(Gtk::ALIGN_CENTER);
    infoGrid.set_valign(Gtk::ALIGN_CENTER);
    infoGrid.set_row_spacing(2);
    infoGrid.set_column_spacing(2);


    usernameLabel.set_text("User Name");
//    infoGrid.attach(usernameLabel, 0, 0, 1, 1);

    infoGrid.attach(username, 0, 0, 2, 1);
    username.set_icon_from_pixbuf(PixMan::getIcon("user", 15));

    passwordLabel.set_text("Password");
//    infoGrid.attach(passwordLabel, 0, 1, 1, 1);
    infoGrid.attach(password, 0, 1, 2, 1);
    password.set_visibility(false);
    password.set_invisible_char(Glib::ustring("·").at(0));
    password.set_icon_from_pixbuf(PixMan::getIcon("lock", 15));

    showPassword.set_label("Show Password");
    showPassword.set_active(false);
    showPassword.set_halign(Gtk::ALIGN_START);
    showPassword.signal_toggled().connect([this] {
        if (this->showPassword.get_active()) {
            password.set_visibility(true);
        } else {
            password.set_visibility(false);
        }
    });
    infoGrid.attach(showPassword, 0, 2, 2, 1);

    signUpBt.set_label("Sign Up");

    signUpBt.signal_clicked().connect([this] {
        SignUp *signUp = new SignUp(this->app);
        this->app->add_window(*signUp);
        signUp->show();
        this->hide();
        this->app->remove_window(*this);
    });

    infoGrid.attach(signUpBt, 0, 3, 2, 1);

    logInBt.set_label("Log In");
    logInBt.signal_clicked().connect([this] {
        spinner.property_active() = true;
        dealer.login(this->username.get_text(), this->password.get_text(),
                     [&](std::vector<PacketInfo *> &plist, std::vector<GroupInfo *> &glist,
                         std::vector<ChatInfo *> &clist) {
                         std::cout << "Log In Success" << std::endl;
                         dealer.getMyprofile([&](UserInfo *me) {
                             std::cout << "Get MyProfile Success" << std::endl;
                             dispatcher.connect([&] {
                                 std::cout << "Dispatcher Log In Success" << std::endl;
                                 spinner.property_active() = false;
                                 receiver = new Receiver(plist, glist, clist, me);
                                 receiver->debug();
                                 std::cout<<"Receiver Finished"<<std::endl;

                                 mainWindow = new MainWindow(this->app, receiver->plist, receiver->glist,
                                                             receiver->clist);
                                 receiver->mainWindow = mainWindow;
                                 std::cout << "Finished?" << std::endl;
                                 this->app->add_window(*(this->mainWindow));
                                 this->mainWindow->show();
                                 this->hide();
                                 this->app->remove_window(*this);
                             });
                             dispatcher.emit();
                         }, [this](std::string error) {
                             spinner.property_active() = false;
                             std::cout << error << std::endl;
                         });
                     }, [this](std::string error) {
                    spinner.property_active() = false;
                    std::cout << error << std::endl;
                });

    });
    infoGrid.attach(logInBt, 0, 4, 2, 1);


    show_all_children();
}

LogIn::~LogIn() {}
