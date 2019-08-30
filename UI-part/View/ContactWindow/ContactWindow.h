//
// Created by ervinxie on 8/29/19.
//

#ifndef GTKMM_CONTACTWINDOW_H
#define GTKMM_CONTACTWINDOW_H

#include <gtkmm.h>
#include "ContactList.h"
class ContactWindow : public Gtk::HBox{

public:
    ContactWindow();
    virtual ~ContactWindow();

protected:
    ContactList contactList;


};


#endif //GTKMM_CONTACTWINDOW_H
