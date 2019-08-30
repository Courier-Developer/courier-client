//
// Created by ervinxie on 8/29/19.
//

#ifndef GTKMM_CHATLIST_H
#define GTKMM_CHATLIST_H


#include <gtkmm.h>

class ChatList : public Gtk::VBox {
public:
    ChatList();

    virtual ~ChatList();

protected:
    Gtk::SearchEntry searchEntry;

    class ChatPeep : public Gtk::TreeModel::ColumnRecord {
    public:
        Gtk::TreeModelColumn<Glib::ustring> chatName;
        Gtk::TreeModelColumn<Glib::RefPtr<Gdk::Pixbuf> > avatar;
        Gtk::TreeModelColumn<int> msg_toread;
        ChatPeep() {
            add(chatName);
            add(avatar);
            add(msg_toread);
        }
    }chatPeep;

    Gtk::ScrolledWindow scrolledWindow;
    Gtk::TreeView chatListView;
    Glib::RefPtr<Gtk::ListStore> refChatPeep;

    Glib::RefPtr<Gtk::TreeSelection> select;

    void on_select_change();
};


#endif //GTKMM_CHATLIST_H
