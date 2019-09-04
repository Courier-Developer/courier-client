//
// Created by ervinxie on 8/30/19.
//

#ifndef COURIER_CLIENT_CONTACTLIST_H
#define COURIER_CLIENT_CONTACTLIST_H


#include <gtkmm.h>
#include "ContactInfo.h"

class ContactList : public Gtk::VBox {
public:
    ContactList(ContactWindow *contactWindow,
                std::vector<PacketInfo *> &plist,
                std::vector<GroupInfo *> &glist,
                bool isCheck = false);

    virtual ~ContactList();

    ContactWindow *contactWindow;
    bool isCheck = true;
    std::map<PacketInfo *, Gtk::TreeModel::iterator> p_iter;
    std::map<UserInfo *, Gtk::TreeModel::iterator> u_iter;
    std::map<GroupInfo *, Gtk::TreeModel::iterator> g_iter;
    Gtk::TreeModel::iterator gp_iter;
    std::vector<PacketInfo *> &plist;
    std::vector<GroupInfo *> &glist;

    const int PACKET = 0, USER = 1, GROUP = 2;
    void addNewPacket(PacketInfo *newPacketInfo);

    void deletePacket(PacketInfo *p);

    void addNewFriend(UserInfo *newUser);

    void deleteFriend(UserInfo *u);

    void addNewGroup(GroupInfo *newGroup);

    void deleteGroup(GroupInfo *g);
    Glib::Dispatcher dispatcher;
    ContactInfo* newUser;
    sigc::connection conn;
protected:

    Gtk::SearchEntry searchEntry;
    Gtk::HBox btBox;
    Gtk::Button addNewFriendBt, addNewGroupBt,addNewPacketBt;

    class Contact : public Gtk::TreeModel::ColumnRecord {
    public:
        Gtk::TreeModelColumn<Glib::ustring> nickName;
        Gtk::TreeModelColumn<Glib::RefPtr<Gdk::Pixbuf> > avatar;
        Gtk::TreeModelColumn<Glib::ustring> others;
        Gtk::TreeModelColumn<int> type;
        Gtk::TreeModelColumn<bool> checked;
        Gtk::TreeModelColumn<int> sortPriority;
        Gtk::TreeModelColumn<PacketInfo *> p;
        Gtk::TreeModelColumn<UserInfo *> u;
        Gtk::TreeModelColumn<GroupInfo *> g;

        Contact() {
            add(nickName);
            add(avatar);
            add(others);
            add(type);

            add(sortPriority);
            add(checked);
            add(p);
            add(u);
            add(g);
        }
    } contact;

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
