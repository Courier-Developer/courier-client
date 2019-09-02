//
// Created by ervinxie on 9/1/19.
//

#include "../implement.h"

GroupContactInfo::GroupContactInfo() {

    refAvatar = Gdk::Pixbuf::create_from_file("/home/ervinxie/Downloads/f7074b005cd6a206f6fb94392214c5b6.jpeg");
    refAvatar = refAvatar->scale_simple(64, 64, Gdk::INTERP_BILINEAR);
    Gtk::Image *avatarImg = Gtk::manage(new Gtk::Image(refAvatar));

    avatarNameBox.pack_start(*avatarImg);

    groupName.set_text("Group Name");
    avatarNameBox.pack_start(groupName);

    pack_start(avatarNameBox, Gtk::PACK_SHRINK);

    groupNotice.set_text("Notification");
    pack_start(groupNotice, Gtk::PACK_SHRINK);

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

    for (int i = 0; i < 10; i++) {
        auto row = *(refListStore->append());

        row[groupContact.nickName] = "GroupMember Name";
        auto ava = Gdk::Pixbuf::create_from_file("/home/ervinxie/Downloads/f7074b005cd6a206f6fb94392214c5b6.jpeg");
        ava = ava->scale_simple(24, 24, Gdk::INTERP_BILINEAR);
        row[groupContact.avatar] = ava;
    }

    show_all_children();
}

GroupContactInfo::GroupContactInfo(GroupInfo *group) {
    GroupContactInfo();
    changeGroup(group);
}

void GroupContactInfo::changeGroup(GroupInfo *group) {

}

GroupContactInfo::~GroupContactInfo() {

}
