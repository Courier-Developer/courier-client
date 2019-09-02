//
// Created by ervinxie on 8/30/19.
//

#include "../implement.h"
#include <string>
#include <iostream>

ContactList::ContactList() {
    set_margin_top(5);
    set_spacing(5);

    pack_start(searchEntry, Gtk::PACK_SHRINK);
    searchEntry.signal_search_changed().connect([this]() {
        if (searchEntry.get_text() == "") {
            contacts.collapse_all();
        } else {
            contacts.expand_all();
        }
        filter->refilter();
    });

    scrolledWindow.add(contacts);
    pack_start(scrolledWindow);

    refTreeStore = Gtk::TreeStore::create(contact);

    filter = Gtk::TreeModelFilter::create(refTreeStore);
    filter->set_visible_func(
            [this](const Gtk::TreeModel::const_iterator &iter) -> bool {
                Gtk::TreeModel::Row row = *iter;
                if (row[contact.isPacket])
                    return true;
                Glib::ustring s = row[contact.nickName];
                s = s.lowercase();
                if (s.find(this->searchEntry.get_text().lowercase()) != Glib::ustring::npos) {
                    return true;
                } else {
                    return false;
                }
            }
    );

    sort = Gtk::TreeModelSort::create(filter);
    sort->set_sort_column(contact.sortPriority, Gtk::SORT_DESCENDING);


    contacts.set_model(sort);
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
    row[contact.sortPriority] = 40;

    for (int i = 0; i < 10; i++) {
        Gtk::TreeModel::Row childRow = *(refTreeStore->append(row.children()));
        childRow[contact.nickName] = "Nick Name " + std::to_string(i);
        auto ava = Gdk::Pixbuf::create_from_file("/home/ervinxie/Downloads/f7074b005cd6a206f6fb94392214c5b6.jpeg");
        ava = ava->scale_simple(64, 64, Gdk::INTERP_BILINEAR);
        childRow[contact.avatar] = ava;
        childRow[contact.others] = "Others";
        childRow[contact.sortPriority] = i * 10;

    }

    row = *(refTreeStore->append());

    row[contact.nickName] = "Black List";
    row[contact.isPacket] = true;
    row[contact.sortPriority] = 50;
    for (int i = 0; i < 5; i++) {
        Gtk::TreeModel::Row childRow = *(refTreeStore->append(row.children()));
        childRow[contact.nickName] = "Nick Name " + std::to_string(i * i);
        auto ava = Gdk::Pixbuf::create_from_file("/home/ervinxie/Downloads/f7074b005cd6a206f6fb94392214c5b6.jpeg");
        ava = ava->scale_simple(64, 64, Gdk::INTERP_BILINEAR);
        childRow[contact.avatar] = ava;
        childRow[contact.others] = "Others";
        childRow[contact.sortPriority] = i;
    }


    show_all_children();
}


ContactList::~ContactList() {

}
