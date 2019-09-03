//
// Created by ervinxie on 8/28/19.
//

#ifndef GTKMM_MAINWINDOW_H
#define GTKMM_MAINWINDOW_H


#include <gtkmm.h>
#include "LogIn.h"

const int CHATS = 1;
const int CONTACTS = 2;
const int OTHERS = 3;


class MainWindow : public Gtk::Window{
public:
    MainWindow(Glib::RefPtr<Gtk::Application> app,
            std::vector<PacketInfo *>& plist,
            std::vector<GroupInfo *>& glist,
            std::vector<ChatInfo *>& clist);
    virtual ~MainWindow();
    Glib::RefPtr<Gtk::Application> app;

    std::vector<PacketInfo *>& plist;
    std::vector<GroupInfo *>& glist;
    std::vector<ChatInfo *>& clist;

    ChatWindow chatWindow;
    ContactWindow contactWindow;
    OtherWindow otherWindow;
    void changeWindow(int to);
protected:



    Gtk::VBox avatar_button_box;
    Gtk::HBox box;
    Gtk::Image avatar;
    Gtk::Button chats_bt,contacts_bt,others_bt;


    Gtk::Frame windowFrame;




};


#endif //GTKMM_MAINWINDOW_H
