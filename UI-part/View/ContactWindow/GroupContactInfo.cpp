//
// Created by ervinxie on 9/1/19.
//

#include "../implement.h"
#include "GroupContactInfo.h"


GroupContactInfo::GroupContactInfo() {
    set_valign(Gtk::ALIGN_FILL);
    set_halign(Gtk::ALIGN_FILL);
    set_border_width(10);
    set_size_request(100, 300);
    set_spacing(10);
    refAvatar = PixMan::TryOrDefaultUserAva(64,"");
    refAvatar = refAvatar->scale_simple(64, 64, Gdk::INTERP_BILINEAR);
    avatarImage.property_pixbuf() = refAvatar;
    avatarImage.get_style_context()->add_class("avatar");
    avatarNameBox.pack_start(avatarImage);
    groupName.set_text("Group Name");
    avatarNameBox.pack_start(groupName);

    pack_start(avatarNameBox, Gtk::PACK_SHRINK);
    avatarNameBox.set_hexpand(true);
    avatarNameBox.set_halign(Gtk::ALIGN_START);

    groupNotice.set_text("Notification");
    pack_start(groupNotice, Gtk::PACK_SHRINK);


    pack_start(scrolledWindow);
    scrolledWindow.add(contacts);
    contacts.append_column("avatar", groupContact.avatar);
    contacts.append_column("nickName", groupContact.nickName);
    contacts.append_column("others", groupContact.others);
    contacts.set_headers_visible(false);

    refListStore = Gtk::ListStore::create(groupContact);
    sort = Gtk::TreeModelSort::create(refListStore);
    sort->set_default_sort_func([this](const Gtk::TreeModel::iterator &a, const Gtk::TreeModel::iterator &b) -> int {
        int x = (*a)[groupContact.sortPriority] - (*b)[groupContact.sortPriority];
        if (x > 0) {
            return -1;
        } else if (x == 0) {
            return 0;
        } else {
            return 1;
        }
    });

    filter = Gtk::TreeModelFilter::create(sort);
    filter->set_visible_func([this](const Gtk::TreeModel::const_iterator &iter) -> bool {
        Gtk::TreeModel::Row row = *iter;
        Glib::ustring s = row[groupContact.nickName];
        s = s.lowercase();
        if (s.find(this->searchEntry.get_text().lowercase()) != Glib::ustring::npos) {
            return true;
        } else {
            return false;
        }
    });
    contacts.set_model(filter);

    startChat.set_label("Start Chat");
    pack_end(startChat,Gtk::PACK_SHRINK);

    startChat.signal_clicked().connect([this]{
        if(this->group){
            auto c= dealer.chatWith(this->group);
            receiver->mainWindow->changeWindow(CHATS);
            receiver->mainWindow->chatWindow->chatList.addChat(c);
            receiver->mainWindow->chatWindow->changeTo(c);
        }
    });


    pack_end(quitGroupBt, Gtk::PACK_SHRINK);
    quitGroupBt.set_label("Quit This Group");
    quitGroupBt.signal_clicked().connect([this] {
        Gtk::Dialog dialog;
        dialog.get_content_area()->pack_start(*Gtk::manage(new Gtk::Label("Confirm Quit This Group?")));
        dialog.add_button("Cancel", 0);
        dialog.add_button("OK", 1);
        dialog.show_all_children();
        dialog.set_border_width(10);
        if (dialog.run()==1) {

        }
        else {

        }

    });

    show_all_children();
}

GroupContactInfo::GroupContactInfo(GroupInfo *group) : GroupContactInfo() {
    changeGroup(group);
}

void GroupContactInfo::changeGroup(GroupInfo *group) {
    this->group = group;

    avatarImage.property_pixbuf() = PixMan::TryOrDefaultUserAva(64,group->getAvatarPath());
    groupName.set_text(group->getNickName());
    groupNotice.set_text(group->getNotice());
    refListStore->clear();
    for (auto u:*group->getUsers()) {
        addUserAsMember(u);
    }

}

void GroupContactInfo::addUserAsMember(UserInfo *newUser) {
    auto iter = refListStore->append();
    iter->set_value(groupContact.nickName, Glib::ustring(newUser->getNickName()));
    iter->set_value(groupContact.avatar, PixMan::TryOrDefaultUserAva(24,newUser->getAvatarPath(),newUser->getStatus()==0,newUser->getUserId()));
}

GroupContactInfo::~GroupContactInfo() {
    hide();
}

