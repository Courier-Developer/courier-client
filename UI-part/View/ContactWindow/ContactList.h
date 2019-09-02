//
// Created by ervinxie on 8/30/19.
//

#ifndef COURIER_CLIENT_CONTACTLIST_H
#define COURIER_CLIENT_CONTACTLIST_H


#include <gtkmm.h>
#include "ContactInfo.h"

class ContactList :public Gtk::VBox{
public:
    ContactList(ContactWindow* contactWindow,bool isCheck=false);
    virtual ~ContactList();
    ContactWindow* contactWindow;
    bool isCheck=true;
protected:
    Gtk::SearchEntry searchEntry;
    Gtk::HBox btBox;
    Gtk::Button addNewUser,addNewGroup;

    class Contact:public Gtk::TreeModel::ColumnRecord{
    public:
        Gtk::TreeModelColumn<Glib::ustring> nickName;
        Gtk::TreeModelColumn<Glib::RefPtr<Gdk::Pixbuf> > avatar;
        Gtk::TreeModelColumn<Glib::ustring> others;
        Gtk::TreeModelColumn<bool> isPacket;
        Gtk::TreeModelColumn<bool> checked;
        Gtk::TreeModelColumn<int> sortPriority;
        Contact(){
            add(nickName);
            add(avatar);
            add(others);
            add(isPacket);
            add(sortPriority);
            add(checked);
        }
    }contact;

    Gtk::ScrolledWindow scrolledWindow;
    Gtk::TreeView contacts;
    Gtk::CellRendererToggle ck_render;
    Gtk::TreeView::Column ck;
    Glib::RefPtr<Gtk::TreeStore> refTreeStore;
    Glib::RefPtr<Gtk::TreeModelFilter> filter;
    Glib::RefPtr<Gtk::TreeModelSort> sort;
    Glib::RefPtr<Gtk::TreeSelection> select;
};


#endif //COURIER_CLIENT_CONTACTLIST_H
