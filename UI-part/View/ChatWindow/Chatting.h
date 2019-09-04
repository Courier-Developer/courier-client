//
// Created by ervinxie on 8/29/19.
//

#ifndef GTKMM_CHATTING_H
#define GTKMM_CHATTING_H

#include <gtkmm.h>
#include "ChatList.h"

class Chatting : public Gtk::VBox {
public:
    Chatting(ChatWindow* chatWindow,ChatInfo* c);
    virtual ~Chatting();
    ChatWindow *chatWindow;
    void addMessage(MessageInfo*);
    ChatInfo* c;
protected:
    Gtk::Label chatName;

    Gtk::ScrolledWindow scrolledWindow;

    Gtk::VBox msgList;

    Gtk::HBox tools;
    Gtk::Button expressionBt;
    Gtk::Button fileBt;
    Gtk::Button historyBt;
    Gtk::Button imageBt;

    Gtk::Button chatDetailBt,cancelBt;


    Gtk::TextView msgEdit;
    Glib::RefPtr<Gtk::TextBuffer> refMsgText;

    ContactInfo* contactInfo;
    GroupContactInfo* groupContactInfo;
    bool isGroup=0;
};


#endif //GTKMM_CHATTING_H
