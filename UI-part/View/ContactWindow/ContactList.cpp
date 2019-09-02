//
// Created by ervinxie on 8/30/19.
//

#include "../implement.h"
#include <string>
#include <iostream>

ContactList::ContactList(ContactWindow *contactWindow, bool isCheck) : contactWindow(contactWindow),
                                                                       isCheck(isCheck) {
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

    if (isCheck == false) {
        btBox.pack_start(addNewUser);

        addNewUser.set_label("Add New User");
        addNewUser.signal_clicked().connect([this] {
            Gtk::Dialog dialog;
            Gtk::SearchEntry newUserEntry;
            ContactInfo newUser;
            newUserEntry.set_placeholder_text("Enter the target UserName");
            newUserEntry.signal_changed().connect([&] {
                newUserEntry.get_text();
            });

            dialog.get_content_area()->pack_start(newUserEntry);
            dialog.get_content_area()->pack_start(newUser);

            dialog.add_button("Back", 0);
            dialog.show_all_children();
            dialog.run();
        });

        btBox.pack_start(addNewGroup);
        addNewGroup.set_label("Add New Group");
        addNewGroup.signal_clicked().connect([this] {
            Gtk::Dialog dialog;
            dialog.set_size_request(300, 400);
            dialog.get_content_area()->pack_start(*Gtk::manage(new Gtk::Label("Select Friends")));

            ContactList *gselect = Gtk::manage(new ContactList(nullptr, true));
            gselect->set_size_request(-1, 400);
            dialog.get_content_area()->pack_start(*gselect);

            dialog.add_button("Back", 0);
            dialog.show_all_children();
            dialog.run();
        });
        pack_start(btBox, Gtk::PACK_SHRINK);
    }


    scrolledWindow.add(contacts);
    pack_start(scrolledWindow);

    refTreeStore = Gtk::TreeStore::create(contact);

    if(isCheck==false) {
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
    }else{
        contacts.set_model(refTreeStore);
    }

    if (isCheck) {
        ck.set_title("Check");
        ck.pack_start(ck_render);
        ck.set_cell_data_func(ck_render, [this](Gtk::CellRenderer *c /* renderer */,const Gtk::TreeModel::iterator &iter) {
            if (iter) {
                ck_render.property_active() = iter->get_value(contact.checked);
            }
        });
        contacts.append_column(ck);
        ck_render.signal_toggled().connect([this](const Glib::ustring &path) {
//            std::cout << path << std::endl;
            auto c = refTreeStore->get_iter(path);

            bool checked = !c->get_value(contact.checked);
            c->set_value(contact.checked, checked);
            ck_render.property_active() = checked;
//            std::cout << checked << std::endl;
            for (auto kid:c->children()) {
                auto row = *kid;
                kid->set_value(contact.checked, checked);
                row[contact.checked] = checked;

            }
        });
    }

    contacts.append_column("avatar", contact.avatar);
    contacts.append_column("Nick Name", contact.nickName);
    contacts.append_column("others", contact.others);
    contacts.set_level_indentation(0);
    contacts.set_headers_visible(false);

    if (isCheck == false) {
        select = contacts.get_selection();
        select->signal_changed().connect([this] {
            Gtk::TreeModel::iterator iter = select->get_selected();
            if (iter) {
                Gtk::TreeModel::Row row = *iter;
                std::cout << "The " << row[contact.nickName] << " Clicked. " << std::endl;
                //Do something with the row.
            }
        });
    }


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
