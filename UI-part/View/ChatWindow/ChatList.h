//
// Created by ervinxie on 8/29/19.
//

#ifndef GTKMM_CHATLIST_H
#define GTKMM_CHATLIST_H


#include <gtkmm.h>
#include "../predeclare.h"

class ChatList : public Gtk::VBox {
public:
    ChatList(ChatWindow *chatWindow, std::vector<ChatInfo *> &clist);

    virtual ~ChatList();

    ChatWindow *chatWindow;
    std::vector<ChatInfo *> &clist;
    std::map<ChatInfo*,Gtk::TreeModel::iterator> c_iter;
    const int USER = 1;
    const int GROUP = 2;
protected:
    Gtk::SearchEntry searchEntry;

    class ChatPeep : public Gtk::TreeModel::ColumnRecord {
    public:
        Gtk::TreeModelColumn<Glib::ustring> chatName;
        Gtk::TreeModelColumn<Glib::RefPtr<Gdk::Pixbuf> > avatar;
        Gtk::TreeModelColumn<int> msg_toread;
        Gtk::TreeModelColumn<Glib::ustring> lastMsgTime;
        Gtk::TreeModelColumn<int> sortPriority;
        Gtk::TreeModelColumn<int> type;
        Gtk::TreeModelColumn<ChatInfo *> c;

        ChatPeep() {
            add(chatName);
            add(avatar);
            add(msg_toread);
            add(lastMsgTime);
            add(sortPriority);
            add(type);
            add(c);
        }
    } chatPeep;

    Gtk::ScrolledWindow scrolledWindow;
    Gtk::TreeView chatListView;

    Glib::RefPtr<Gtk::ListStore> refChatPeep;
    Glib::RefPtr<Gtk::TreeModelFilter> filter;
    Glib::RefPtr<Gtk::TreeModelSort> sort;

    Glib::RefPtr<Gtk::TreeSelection> select;

    void addChat(ChatInfo *newChat);

};


#endif //GTKMM_CHATLIST_H
