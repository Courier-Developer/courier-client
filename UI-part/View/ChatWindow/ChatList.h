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

        Gtk::TreeModelColumn<Glib::RefPtr<Gtk::Button> >Bt;

        Gtk::TreeModelColumn<Glib::ustring> lastMsgTime;

        Gtk::TreeModelColumn<int> sortPriority;

        ChatPeep() {
            add(chatName);
            add(avatar);
            add(msg_toread);
            add(Bt);
            add(lastMsgTime);
            add(sortPriority);
        }
    }chatPeep;

    Gtk::ScrolledWindow scrolledWindow;
    Gtk::TreeView chatListView;
    Glib::RefPtr<Gtk::ListStore> refChatPeep;
    Glib::RefPtr<Gtk::TreeModelFilter> filter;
    Glib::RefPtr<Gtk::TreeModelSort> sort;

    Glib::RefPtr<Gtk::TreeSelection> select;

    void on_select_change();
};


#endif //GTKMM_CHATLIST_H
