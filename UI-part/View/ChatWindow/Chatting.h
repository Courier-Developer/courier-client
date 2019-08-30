//
// Created by ervinxie on 8/29/19.
//

#ifndef GTKMM_CHATTING_H
#define GTKMM_CHATTING_H

#include <gtkmm.h>
class Chatting : public  Gtk::VBox{
public:
    Chatting();
    virtual ~Chatting();

protected:
    Gtk::Label chatName;
    Gtk::ScrolledWindow scrolledWindow;

    Gtk::TreeView msgList;
    Gtk::Toolbar toolbar;
    Gtk::TextView msgEdit;

    Glib::RefPtr<Gtk::TextBuffer> refMsgText;


};


#endif //GTKMM_CHATTING_H
