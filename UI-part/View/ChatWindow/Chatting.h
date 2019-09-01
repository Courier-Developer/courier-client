//
// Created by ervinxie on 8/29/19.
//

#ifndef GTKMM_CHATTING_H
#define GTKMM_CHATTING_H

#include <gtkmm.h>

class ChatWindow;
class Chatting : public  Gtk::VBox{
public:
    Chatting();
    virtual ~Chatting();
    ChatWindow* chatWindow;

protected:
    Gtk::Label chatName;
    Gtk::ScrolledWindow scrolledWindow;

    Gtk::TreeView msgList;

    Gtk::HBox tools;
    Gtk::Button expressionBt;
    Gtk::Button fileBt;
    Gtk::Button chatDetailBt;


    Gtk::TextView msgEdit;

    Glib::RefPtr<Gtk::TextBuffer> refMsgText;


};


#endif //GTKMM_CHATTING_H
