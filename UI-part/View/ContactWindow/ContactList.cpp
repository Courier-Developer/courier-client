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
    std::cout << "Contact List Building" << std::endl;

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

        addNewFriendBt.set_image(*Gtk::manage(new Gtk::Image(PixMan::getIcon("adduser", 32))));
        addNewFriendBt.signal_clicked().connect([this] {
            this->dialog = new Gtk::Dialog;
            this->dframe = new Gtk::Frame;
            Gtk::SearchEntry newUserEntry;
            this->newUser = new ContactInfo(receiver->me, 64, 10);
            Gtk::Button se("Search");
            this->dialog->get_content_area()->pack_start(newUserEntry);
            this->dialog->get_content_area()->pack_start(se, Gtk::PACK_SHRINK);

            newUserEntry.set_placeholder_text("Enter the target UserName");
            se.signal_clicked().connect([&] {

                dealer.queryUser(newUserEntry.get_text(), [this](UserInfo *u) {
                    std::cout << "Dispacther OK" << std::endl;
                    if (conn.connected()) {
                        conn.disconnect();
                    }
                    conn = dispatcher.connect([=] {
                        std::cout << "query OK" << std::endl;
                        dframe->remove();
                        dframe->add(*Gtk::manage(new ContactInfo(u, 64, 0)));
                        this->dialog->show_all_children();
                    });
                    dispatcher.emit();
                }, [this](std::string err) {
                    std::cout << err << std::endl;
                });

            });


            dialog->get_content_area()->pack_start(*dframe);
            dframe->add(*(this->newUser));
            dialog->add_button("Back", 0);
            dialog->show_all_children();
            dialog->run();
        });

        btBox.pack_start(addNewGroupBt);
        addNewGroupBt.set_image(*Gtk::manage(new Gtk::Image(PixMan::getIcon("addteam", 32))));
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
            cancel->signal_clicked().connect([&] {
                dialog.hide();
            });

            auto confirm = Gtk::manage(new Gtk::Button("Confirm"));
            dialog.get_content_area()->pack_end(*confirm);
            confirm->signal_clicked().connect([&] {
                vector<int> v;
                for (auto iter:(gselect->refTreeStore)->children()) {
                    std::cout<<iter->get_value(contact.nickName)<<std::endl;
                    for (auto kid:iter->children()) {
                        std::cout << kid->get_value(contact.nickName) << std::endl;
                        if (kid->get_value(contact.checked)) {
                            if (kid->get_value(contact.type) == USER) {
                                v.push_back(kid->get_value(contact.u)->getUserId());
                            }
                        }
                    }
                }
                for (int i:v) {
                    std::cout << i << std::endl;
                }

                dialog.hide();
            });

            dialog.show_all_children();
            dialog.run();
        });

        btBox.pack_start(addNewPacketBt);
        addNewPacketBt.set_image(*Gtk::manage(new Gtk::Image(PixMan::getIcon("plus-square", 32))));
        addNewPacketBt.signal_clicked().connect([this] {
            Gtk::Dialog dialog;
            dialog.set_border_width(10);
            dialog.set_size_request(100, 100);
            Glib::ustring info = "Add a New Packet";
            Gtk::Label *label = Gtk::manage(new Gtk::Label(info));
            Gtk::Entry *entry = Gtk::manage(new Gtk::Entry);
            entry->set_placeholder_text("Name the Packet");
            label->set_line_wrap(true);
            dialog.get_content_area()->pack_start(*label);
            dialog.get_content_area()->pack_start(*entry);
            dialog.add_button("Cancel", 0);
            dialog.add_button("Confirm", 1);
            dialog.show_all_children();
            int results = dialog.run();
            if (results == 1) {
                dealer.addPacket(entry->get_text(), [this](PacketInfo *np) {
                    if (conn.connected()) {
                        conn.disconnect();
                    }
                    conn = dispatcher.connect([=] {
                        addNewPacket(np);
                    });
                    dispatcher.emit();
                }, [this](std::string err) {
                    if (conn.connected()) {
                        conn.disconnect();
                    }
                    conn = dispatcher.connect([=] {
                        Gtk::MessageDialog dialog(err);
                        dialog.run();
                    });
                });
            }

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
                if (iter->get_value(contact.type) == USER) {
                    this->contactWindow->frame.remove();
                    this->contactWindow->frame.add(*Gtk::manage(new ContactInfo(iter->get_value(contact.u))));
                    this->contactWindow->frame.show_all_children();
                } else if (iter->get_value(contact.type) == GROUP) {
                    this->contactWindow->frame.remove();
                    this->contactWindow->frame.add(*Gtk::manage(new GroupContactInfo(iter->get_value(contact.g))));
                    this->contactWindow->frame.show_all_children();
                } else if (iter->get_value(contact.type) == PACKET) {
                    this->contactWindow->frame.remove();
                    this->contactWindow->frame.add(*Gtk::manage(new PacketContactInfo(iter->get_value(contact.p))));
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
        gp_iter->set_value(contact.p, (PacketInfo *) nullptr);
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
    Gtk::TreeModel::iterator iter;
    if (p_iter.count(newPacketInfo) == 0) {
        iter = refTreeStore->append();
        p_iter[newPacketInfo] = iter;
    } else {
        iter = p_iter[newPacketInfo];
    }
    iter->set_value(contact.type, PACKET);
    iter->set_value(contact.nickName, Glib::ustring(newPacketInfo->getName()));
    iter->set_value(contact.sortPriority, newPacketInfo->getPriority());
    iter->set_value(contact.p, newPacketInfo);
}

void ContactList::deletePacket(PacketInfo *p) {
    if (p_iter.count(p) && p->getUsers()->empty()) {
        auto iter = p_iter[p];
        refTreeStore->erase(iter);
        p_iter.erase(p);
    }
}


void ContactList::addNewFriend(UserInfo *newUser) {
    Gtk::TreeModel::iterator iter;
    if (u_iter.count(newUser) == 0) {
        iter = refTreeStore->append(p_iter[newUser->getInPacket()]->children());
        u_iter[newUser] = iter;
    } else {
        iter = u_iter[newUser];
    }
    iter->set_value(contact.nickName, Glib::ustring(newUser->getNickName()));
    iter->set_value(contact.avatar, PixMan::TryOrDefaultUserAva(24, newUser->getAvatarPath()));
    iter->set_value(contact.u, newUser);
    iter->set_value(contact.type, USER);
    iter->set_value(contact.sortPriority, 0);
}

void ContactList::deleteFriend(UserInfo *u) {
    if (u_iter.count(u)) {
        auto iter = u_iter[u];
        refTreeStore->erase(iter);
        u_iter.erase(u);
    }
}


void ContactList::addNewGroup(GroupInfo *newGroup) {
    Gtk::TreeModel::iterator iter;
    if (g_iter.count(newGroup) == 0) {
        iter = refTreeStore->append(gp_iter->children());
        g_iter[newGroup] = iter;
    } else {
        iter = g_iter[newGroup];
    }
    iter->set_value(contact.nickName, Glib::ustring(newGroup->getNickName()));
    iter->set_value(contact.avatar, PixMan::TryOrDefaultUserAva(24, newGroup->getAvatarPath()));
    iter->set_value(contact.g, newGroup);
    iter->set_value(contact.type, GROUP);
    iter->set_value(contact.sortPriority, 0);

}

void ContactList::deleteGroup(GroupInfo *g) {
    if (g_iter.count(g)) {
        auto iter = g_iter[g];
        refTreeStore->erase(iter);
        g_iter.erase(g);
    }
}





