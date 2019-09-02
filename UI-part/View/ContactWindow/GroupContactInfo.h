//
// Created by ervinxie on 9/1/19.
//

#ifndef COURIER_CLIENT_GROUPCONTACTINFO_H
#define COURIER_CLIENT_GROUPCONTACTINFO_H

#include <gtkmm.h>
#include "ContactWindow.h"
#include "../../../Logic_Part/UI-Interface/GroupInfo.h"
class GroupContactInfo : public Gtk::VBox{
public:
    GroupContactInfo();
    GroupContactInfo(GroupInfo* group);
    virtual ~GroupContactInfo();
    void changeGroup(GroupInfo* group);
    GroupInfo* group;
protected:
    void ChangeGroup(GroupInfo* group);

    Glib::RefPtr<Gdk::Pixbuf> refAvatar;
    Gtk::Label groupName;
    Gtk::HBox avatarNameBox;
    Gtk::Label groupNotice;

    Gtk::ScrolledWindow scrolledWindow;
    Gtk::SearchEntry searchEntry;
    Gtk::TreeView contacts;
    Glib::RefPtr<Gtk::ListStore> refListStore;
    Glib::RefPtr<Gtk::TreeModelFilter> filter;
    Glib::RefPtr<Gtk::TreeModelSort> sort;

    class GroupContact: public Gtk::TreeModel::ColumnRecord{
    public:
        Gtk::TreeModelColumn<Glib::ustring> nickName;
        Gtk::TreeModelColumn<Glib::RefPtr<Gdk::Pixbuf> > avatar;
        Gtk::TreeModelColumn<Glib::ustring> others;
        Gtk::TreeModelColumn<int> sortPriority;
        GroupContact(){
            add(nickName);
            add(avatar);
            add(others);
            add(sortPriority);
        }
    }groupContact;

};


#endif //COURIER_CLIENT_GROUPCONTACTINFO_H
