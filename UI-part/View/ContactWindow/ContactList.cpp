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
    contacts.set_model(refTreeStore);
    contacts.set_headers_visible(false);
    contacts.append_column("avatar", contact.avatar);
    contacts.append_column("Nick Name", contact.nickName);
    contacts.append_column("others", contact.others);
    contacts.set_level_indentation(0);


    contacts.set_enable_search(true);
    contacts.set_search_entry(searchEntry);

    contacts.set_search_equal_func(sigc::mem_fun(*this, &ContactList::on_search_equal));


    select = contacts.get_selection();
    select->signal_changed().connect(sigc::mem_fun(*this, &ContactList::on_select_change));


    Gtk::TreeModel::Row row = *(refTreeStore->append());

    row[contact.nickName] = "Group";

    for (int i = 0; i < 10; i++) {
        Gtk::TreeModel::Row childRow = *(refTreeStore->append(row.children()));
        childRow[contact.nickName] = "Nick Name " + std::to_string(i);
        auto ava = Gdk::Pixbuf::create_from_file("/home/ervinxie/Downloads/f7074b005cd6a206f6fb94392214c5b6.jpeg");
        ava = ava->scale_simple(64, 64, Gdk::INTERP_BILINEAR);
        childRow[contact.avatar] = ava;
        childRow[contact.others] = "Others";

    }

    row = *(refTreeStore->append());


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

bool ContactList::on_search_equal(const Glib::RefPtr<Gtk::TreeModel> &model, int column, const Glib::ustring &key,
                                  const Gtk::TreeModel::iterator &iter) {
    Gtk::TreeModel::Row row = *iter;
    Glib::ustring s = row[contact.nickName];
    if(s.find(key))
        return true;
    s = row[contact.others];
    if(s.find(key))
        return true;


    return false;
}

ContactList::~ContactList() {

}

void ContactList::on_select_change() {
    Gtk::TreeModel::iterator iter = select->get_selected();
    if (iter) {
        Gtk::TreeModel::Row row = *iter;
        std::cout << "The " << row[contact.nickName] << " Clicked. " << std::endl;
        //Do something with the row.
    }
}
