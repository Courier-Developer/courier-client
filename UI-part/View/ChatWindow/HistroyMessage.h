//
// Created by ervinxie on 9/3/19.
//

#ifndef COURIER_CLIENT_HISTROYMESSAGE_H
#define COURIER_CLIENT_HISTROYMESSAGE_H

#include "ChatWindow.h"
class HistroyMessage :public Gtk::VBox{
public:
    HistroyMessage(ChatInfo* chatInfo);
    ChatInfo* chatInfo;
    void addMessage(MessageInfo* msg);
protected:
    Gtk::SearchEntry searchEntry;
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

};


#endif //COURIER_CLIENT_HISTROYMESSAGE_H
