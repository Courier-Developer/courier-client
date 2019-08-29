//
// Created by ervinxie on 8/28/19.
//

#include "LogIn.h"
#include "MainWindow.h"
#include <iostream>
LogIn::LogIn() :
        usernameLable("User Name"),
        passwordLable("Password"),
        logInBt("Log In"),
        signInBt("Sign In") {
    std::cout<<"Building Log In Window"<<std::endl;

    set_title("Welcome to Courier");
    set_position(Gtk::WIN_POS_CENTER);
    grid.set_border_width(10);
    grid.set_halign(Gtk::ALIGN_CENTER);
    grid.set_valign(Gtk::ALIGN_CENTER);
    set_size_request(300,50);

    add(grid);


    grid.attach(usernameLable, 0, 0, 1, 1);
    grid.attach(username, 1, 0, 1, 1);

    grid.attach(passwordLable, 0, 1, 1, 1);
    grid.attach(password, 1, 1, 1, 1);
    password.set_visibility(false);
    password.set_invisible_char('*');

    grid.attach(signInBt, 0, 2, 1, 1);
    grid.attach(logInBt, 1, 2, 1, 1);


    logInBt.signal_clicked().connect(sigc::mem_fun(*this,&LogIn::on_login));
    signInBt.signal_clicked().connect(sigc::mem_fun(*this,&LogIn::on_signin));

    show_all_children();
}

LogIn::~LogIn() {}

void LogIn::on_login() {
    std::cout<<"Log In Button Clicked"<<std::endl;
    MainWindow* mainWindow = new MainWindow;


    (*app)->add_window(*mainWindow);
    mainWindow->show();

    this->hide();
    (*app)->remove_window(*this);
}

void LogIn::on_signin() {
    std::cout<<"Sign In Button Clicked"<<std::endl;
}