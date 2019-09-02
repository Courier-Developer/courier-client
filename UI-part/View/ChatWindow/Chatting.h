//
// Created by ervinxie on 8/29/19.
//

#ifndef GTKMM_CHATTING_H
#define GTKMM_CHATTING_H

#include <gtkmm.h>
#include "ChatList.h"

class Chatting : public Gtk::VBox {
public:
    Chatting(ChatWindow* chatWindow);
    virtual ~Chatting();
    ChatWindow *chatWindow;
    void addMessage(Glib::ustring content);
protected:
    Gtk::Label chatName;
    Gtk::ScrolledWindow scrolledWindow;
    Gtk::TreeView msgList;
    class Message : public Gtk::TreeModel::ColumnRecord {
    public:
        Gtk::TreeModelColumn<Glib::ustring> content;
        Gtk::TreeModelColumn<Glib::ustring> senderName;
        Gtk::TreeModelColumn<Glib::RefPtr<Gdk::Pixbuf>> senderAvatar;
        Gtk::TreeModelColumn<Glib::ustring> msgTime;

        Message() {
            add(content);
            add(senderName);
            add(senderAvatar);
            add(msgTime);
        }
    } message;

    Glib::RefPtr<Gtk::ListStore> messages;
    Glib::RefPtr<Gtk::TreeModelFilter> filter;

    Gtk::HBox tools;
    Gtk::Button expressionBt;
    Gtk::Button fileBt;
    Gtk::Button chatDetailBt;

    Gtk::TextView msgEdit;
    Glib::RefPtr<Gtk::TextBuffer> refMsgText;

    ContactInfo* contactInfo;
    GroupContactInfo* groupContactInfo;
    bool isGroup=0;
};


#endif //GTKMM_CHATTING_H
