//
// Created by ervinxie on 8/30/19.
//

#include "../implement.h"
#include "ContactList.h"

#include <string>
#include <iostream>

ContactList::ContactList(ContactWindow *contactWindow, std::vector<PacketInfo *> &plist,
                         std::vector<GroupInfo *> &glist, bool isCheck) :
        contactWindow(contactWindow),
        isCheck(isCheck),
        glist(glist),
        plist(plist) {

    set_margin_top(5);
    set_spacing(5);

    refTreeStore = Gtk::TreeStore::create(contact);
    if (isCheck == false) {
        pack_start(searchEntry, Gtk::PACK_SHRINK);
        searchEntry.signal_search_changed().connect([this]() {
            if (searchEntry.get_text() == "") {
                contacts.collapse_all();
            } else {
                contacts.expand_all();
            }
            filter->refilter();
        });

        btBox.pack_start(addNewFriendBt);

        addNewFriendBt.set_label("Add New User");
        addNewFriendBt.signal_clicked().connect([this] {
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

        btBox.pack_start(addNewGroupBt);
        addNewGroupBt.set_label("Add New Group");
        addNewGroupBt.signal_clicked().connect([this] {
            Gtk::Dialog dialog;
            dialog.set_size_request(300, 400);
            dialog.get_content_area()->pack_start(*Gtk::manage(new Gtk::Label("Select Friends")));
            dialog.set_border_width(10);

            ContactList *gselect = Gtk::manage(new ContactList(nullptr, this->plist, this->glist, true));
            gselect->set_size_request(-1, 400);
            dialog.get_content_area()->pack_start(*gselect);

            auto cancel = Gtk::manage(new Gtk::Button("Cancel"));
            dialog.get_content_area()->pack_end(*cancel);
            cancel->signal_clicked().connect([&]{
                dialog.hide();
            });

            auto confirm = Gtk::manage(new Gtk::Button("Confirm"));
            dialog.get_content_area()->pack_end(*confirm);
            confirm->signal_clicked().connect([&]{
                dialog.hide();
            });

            dialog.show_all_children();
            dialog.run();
        });
        pack_start(btBox, Gtk::PACK_SHRINK);

        filter = Gtk::TreeModelFilter::create(refTreeStore);
        filter->set_visible_func(
                [this](const Gtk::TreeModel::const_iterator &iter) -> bool {
                    Gtk::TreeModel::Row row = *iter;
                    if (row[contact.type] == PACKET)
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
        select = contacts.get_selection();
        select->signal_changed().connect([this] {
            Gtk::TreeModel::iterator iter = select->get_selected();
            if (iter) {
                std::cout << "The " << iter->get_value(contact.nickName) << " Clicked. " << std::endl;
                if(iter->get_value(contact.type)==USER){
                    this->contactWindow->frame.remove();
                    this->contactWindow->frame.add(*Gtk::manage(new ContactInfo(iter->get_value(contact.u))));
                    this->contactWindow->frame.show_all_children();
                }else if(iter->get_value(contact.type)==GROUP){
                    this->contactWindow->frame.remove();
                    this->contactWindow->frame.add(*Gtk::manage(new GroupContactInfo(iter->get_value(contact.g))));
                    this->contactWindow->frame.show_all_children();
                }

            }
        });

        sort = Gtk::TreeModelSort::create(filter);
        sort->set_sort_column(contact.sortPriority, Gtk::SORT_DESCENDING);
        contacts.set_model(sort);
    } else {
        contacts.set_model(refTreeStore);
        ck.set_title("Check");
        ck.pack_start(ck_render);
        ck.set_cell_data_func(ck_render,
                              [this](Gtk::CellRenderer *c /* renderer */, const Gtk::TreeModel::iterator &iter) {
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
    scrolledWindow.add(contacts);
    pack_start(scrolledWindow);
    contacts.append_column("avatar", contact.avatar);
    contacts.append_column("Nick Name", contact.nickName);
    contacts.append_column("others", contact.others);
    contacts.set_level_indentation(0);
    contacts.set_headers_visible(false);

    if (isCheck == false) {
        gp_iter = refTreeStore->append();
        gp_iter->set_value(contact.type, PACKET);
        gp_iter->set_value(contact.nickName, Glib::ustring("群聊"));
        gp_iter->set_value(contact.sortPriority, 0);
        for (auto g:glist) {
            addNewGroup(g);
        }
    }
    for (auto p:plist) {
        if (isCheck == true && (p->getPriority() == 0 || p->getPriority() == -1)) {
            continue;
        }
        if (isCheck == false && p->getPriority() == 0) {
            continue;
        }
        addNewPacket(p);
        for (auto u:*(p->getUsers())) {
            addNewFriend(u);
        }
    }

    show_all_children();
}


ContactList::~ContactList() {

}

void ContactList::addNewPacket(PacketInfo *newPacketInfo) {
    auto iter = refTreeStore->append();
    p_iter[newPacketInfo] = iter;
    iter->set_value(contact.type, PACKET);
    iter->set_value(contact.nickName, Glib::ustring(newPacketInfo->getName()));
    iter->set_value(contact.sortPriority, newPacketInfo->getPriority());
    iter->set_value(contact.p, newPacketInfo);
}

void ContactList::addNewFriend(UserInfo *newUser) {
    auto iter = refTreeStore->append(p_iter[newUser->getInPacket()]->children());
    iter->set_value(contact.nickName, Glib::ustring(newUser->getNickName()));
    Glib::RefPtr<Gdk::Pixbuf> ava;
    try {
        ava = Gdk::Pixbuf::create_from_file(newUser->getAvatarPath());
    }
    catch (...) {
        std::cout << newUser->getNickName() << ":ContactList Avatar Load Failed at" << newUser->getAvatarPath()
                  << std::endl;
        ava = Gdk::Pixbuf::create_from_file("/home/ervinxie/Downloads/f7074b005cd6a206f6fb94392214c5b6.jpeg");
    }
    ava = ava->scale_simple(24, 24, Gdk::INTERP_BILINEAR);
    iter->set_value(contact.avatar, ava);
    iter->set_value(contact.u, newUser);
    iter->set_value(contact.type, USER);
    iter->set_value(contact.sortPriority, 0);
}


void ContactList::addNewGroup(GroupInfo *newGroup) {
    auto iter = refTreeStore->append(gp_iter->children());
    iter->set_value(contact.nickName, Glib::ustring(newGroup->getNickName()));
    Glib::RefPtr<Gdk::Pixbuf> ava;
    try {
        ava = Gdk::Pixbuf::create_from_file(newGroup->getAvatarPath());
    }
    catch (...) {
        std::cout << newGroup->getNickName() << ":ContactList Avatar Load Failed at" << newGroup->getAvatarPath()
                  << std::endl;
        ava = Gdk::Pixbuf::create_from_file("/home/ervinxie/Downloads/f7074b005cd6a206f6fb94392214c5b6.jpeg");
    }
    ava = ava->scale_simple(24, 24, Gdk::INTERP_BILINEAR);
    iter->set_value(contact.avatar, ava);
    iter->set_value(contact.g, newGroup);
    iter->set_value(contact.type, GROUP);
    iter->set_value(contact.sortPriority, 0);

}


