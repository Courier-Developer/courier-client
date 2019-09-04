//
// Created by ervinxie on 8/29/19.
//

#ifndef GTKMM_CONTACTWINDOW_H
#define GTKMM_CONTACTWINDOW_H

#include <gtkmm.h>
#include "ContactList.h"

class ContactWindow : public Gtk::HBox {

public:
    ContactWindow(MainWindow *mainWindow,
                  std::vector<PacketInfo *> &plist,
                  std::vector<GroupInfo *> &glist);

    virtual ~ContactWindow();

    MainWindow *mainWindow;
    std::vector<PacketInfo *> &plist;
    std::vector<GroupInfo *> &glist;
    Gtk::Frame frame;
    ContactList contactList;
protected:


};


#endif //GTKMM_CONTACTWINDOW_H
