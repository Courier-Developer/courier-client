//
// Created by ervinxie on 8/30/19.
//

#include "ContactList.h"
#include <string>
#include <iostream>

ContactList::ContactList() {
    pack_start(searchEntry, Gtk::PACK_SHRINK);

    scrolledWindow.add(contacts);
    pack_start(scrolledWindow);

    refTreeStore = Gtk::TreeStore::create(contact);

    filter = Gtk::TreeModelFilter::create(refTreeStore);
    filter->set_visible_func(
            [this](const Gtk::TreeModel::const_iterator &iter) -> bool {
                std::cout << searchEntry.get_text() << std::endl;
                Gtk::TreeModel::Row row = *iter;
                Glib::ustring s = row[contact.nickName];
                if (s.find(this->searchEntry.get_text()) != Glib::ustring::npos) {
                    return true;
                } else {
                    return false;
                }
            }
    );
    contacts.set_model(filter);

    contacts.set_headers_visible(false);
    contacts.append_column("avatar", contact.avatar);
    contacts.append_column("Nick Name", contact.nickName);
    contacts.append_column("others", contact.others);
    contacts.set_level_indentation(0);


    select = contacts.get_selection();
    select->signal_changed().connect([this] {
        Gtk::TreeModel::iterator iter = select->get_selected();
        if (iter) {
            Gtk::TreeModel::Row row = *iter;
            std::cout << "The " << row[contact.nickName] << " Clicked. " << std::endl;
            //Do something with the row.
        }
    });


    Gtk::TreeModel::Row row = *(refTreeStore->append());

    row[contact.nickName] = "Group";
    row[contact.isPacket] = true;

    for (int i = 0; i < 10; i++) {
        Gtk::TreeModel::Row childRow = *(refTreeStore->append(row.children()));
        childRow[contact.nickName] = "Nick Name " + std::to_string(i);
        auto ava = Gdk::Pixbuf::create_from_file("/home/ervinxie/Downloads/f7074b005cd6a206f6fb94392214c5b6.jpeg");
        ava = ava->scale_simple(64, 64, Gdk::INTERP_BILINEAR);
        childRow[contact.avatar] = ava;
        childRow[contact.others] = "Others";

    }

    row = *(refTreeStore->append());

    row[contact.nickName] = "Black List";
    row[contact.isPacket] = true;
    for (int i = 0; i < 5; i++) {
        Gtk::TreeModel::Row childRow = *(refTreeStore->append(row.children()));
        childRow[contact.nickName] = "Nick Name " + std::to_string(i * i);
        auto ava = Gdk::Pixbuf::create_from_file("/home/ervinxie/Downloads/f7074b005cd6a206f6fb94392214c5b6.jpeg");
        ava = ava->scale_simple(64, 64, Gdk::INTERP_BILINEAR);
        childRow[contact.avatar] = ava;
        childRow[contact.others] = "Others";
    }


    show_all_children();
}


ContactList::~ContactList() {

}
