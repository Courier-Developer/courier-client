//
// Created by ervinxie on 8/28/19.
//

#ifndef GTKMM_CONTACTINFO_H
#define GTKMM_CONTACTINFO_H


#include <gtkmm.h>


class ContactInfo : public Gtk::Grid{
public:
    ContactInfo();
    virtual ~ContactInfo();

protected:
    Glib::RefPtr<Gdk::Pixbuf> avatar;

    Gtk::Label nickName;



};


#endif //GTKMM_CONTACTINFO_H
