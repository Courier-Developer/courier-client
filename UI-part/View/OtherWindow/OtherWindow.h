//
// Created by ervinxie on 8/29/19.
//

#ifndef GTKMM_OTHERWINDOW_H
#define GTKMM_OTHERWINDOW_H

#include <gtkmm.h>
#include "../ContactWindow/PacketContactInfo.h"


class MainWindow;
class LogIn;
class OtherWindow :public Gtk::VBox{
public:
    OtherWindow(MainWindow* mainWindow);
    virtual ~OtherWindow();
    MainWindow* mainWindow;
protected:
    ContactInfo myInfo;
    Gtk::HBox bt_box;
    Gtk::Button editMyInfo;
    Gtk::Button themeChoose;


    Gtk::Button logOut;



};


#endif //GTKMM_OTHERWINDOW_H
