//
// Created by ervinxie on 8/29/19.
//

#ifndef GTKMM_CONTACTWINDOW_H
#define GTKMM_CONTACTWINDOW_H

#include <gtkmm.h>
#include "ContactList.h"

class ContactWindow : public Gtk::HBox{

public:
    ContactWindow(MainWindow* mainWindow);
    virtual ~ContactWindow();
    MainWindow* mainWindow;

protected:
    ContactList contactList;
    ContactInfo* contactInfo;


};


#endif //GTKMM_CONTACTWINDOW_H
