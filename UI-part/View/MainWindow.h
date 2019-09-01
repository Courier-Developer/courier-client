//
// Created by ervinxie on 8/28/19.
//

#ifndef GTKMM_MAINWINDOW_H
#define GTKMM_MAINWINDOW_H


#include <gtkmm.h>
#include "SignUp.h"

const int CHATS = 1;
const int CONTACTS = 2;
const int OTHERS = 3;



class MainWindow : public Gtk::Window{
public:
    MainWindow(Glib::RefPtr<Gtk::Application> app);
    virtual ~MainWindow();
    Glib::RefPtr<Gtk::Application> app;
protected:

    void on_bt(const int& bt_id);

    Gtk::VBox bt_box;
    Gtk::HBox box;
    Gtk::Image avatar;
    Gtk::Button chats_bt,contacts_bt,others_bt;


    Gtk::Frame windowFrame;
    ChatWindow chatWindow;
    ContactWindow contactWindow;
    OtherWindow otherWindow;



};


#endif //GTKMM_MAINWINDOW_H
