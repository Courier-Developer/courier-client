//
// Created by ervinxie on 8/29/19.
//

#include <iostream>
#include "ChatList.h"

ChatList::ChatList() {
    set_size_request(200, 400);
    pack_start(searchEntry, Gtk::PACK_SHRINK);
    set_spacing(10);

    Gtk::Frame* frame = Gtk::manage(new Gtk::Frame);
    frame->add(scrolledWindow);
    frame->set_border_width(0);
    pack_start(*frame);

    scrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    scrolledWindow.add(chatListView);


    refChatPeep = Gtk::ListStore::create(chatPeep);

    chatListView.set_model(refChatPeep);
    chatListView.append_column("Avatar", chatPeep.avatar);
    chatListView.append_column("ChatEntity Name", chatPeep.chatName);
    chatListView.append_column("", chatPeep.msg_toread);
    chatListView.set_headers_visible(false);

    select = chatListView.get_selection();
    select->signal_changed().connect(sigc::mem_fun(*this, &ChatList::on_select_change));


    for (int i = 0; i < 10; i++) {
        Gtk::TreeModel::Row row;
        if (i % 2)
            row = *(refChatPeep->append());
        else
            row = *(refChatPeep->prepend());
        row[chatPeep.chatName] = "ChatEntity Name";
        row[chatPeep.msg_toread] = i;

        auto ava = Gdk::Pixbuf::create_from_file("/home/ervinxie/Downloads/f7074b005cd6a206f6fb94392214c5b6.jpeg");
        ava = ava->scale_simple(64, 64, Gdk::INTERP_BILINEAR);
        row[chatPeep.avatar] = ava;
    }

    show_all_children();
}

ChatList::~ChatList() {

}

void ChatList::on_select_change() {
    Gtk::TreeModel::iterator iter = select->get_selected();
    if (iter) {
        Gtk::TreeModel::Row row = *iter;

        std::cout << "The " << row[chatPeep.chatName] << " " << row[chatPeep.msg_toread] << " Clicked. " << std::endl;
        //Do something with the row.
    }
}
