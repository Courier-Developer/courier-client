//
// Created by ervinxie on 8/28/19.
//

#ifndef GTKMM_CONTACTINFO_H
#define GTKMM_CONTACTINFO_H


#include "../ChatWindow/ShowMessage.h"

class ContactInfo : public Gtk::VBox {
public:
    ContactInfo(UserInfo *userInfo, int avatarSize = 64,int reduce=0);

    virtual ~ContactInfo();

    UserInfo *u;
    std::map<PacketInfo*,Gtk::TreeModel::iterator>p_iter;
    bool dialoging=0;
    Glib::Dispatcher dispatcher;
    sigc::connection conn;
protected:
    Gtk::Grid grid;
    int avatarSize = 64;
    Glib::RefPtr<Gdk::Pixbuf> avatar;
    Gtk::Label nickName;
    Gtk::Label signature;
    Gtk::Button addFriend,
            agreeFriend,
            deleteFriend,
            startChat;

    //Tree model columns:
    class PacketColumn : public Gtk::TreeModel::ColumnRecord
    {
    public:
        PacketColumn()
        { add(p); add(name);}

        Gtk::TreeModelColumn<PacketInfo*> p;
        Gtk::TreeModelColumn<Glib::ustring> name;
    }packetColumn;

    //Child widgets:
    Gtk::ComboBox packetCombo;
    Gtk::CellRendererText packetCell;
    Glib::RefPtr<Gtk::ListStore> refListStore;


};


#endif //GTKMM_CONTACTINFO_H
