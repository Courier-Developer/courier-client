//
// Created by ervinxie on 8/29/19.
//

#include <iostream>
#include "../implement.h"

ChatList::ChatList() {

    set_margin_top(5);
    set_spacing(5);
    set_size_request(200, 400);


    pack_start(searchEntry, Gtk::PACK_SHRINK);
    searchEntry.signal_search_changed().connect([this] {
        filter->refilter();
    });


    pack_start(scrolledWindow);
    scrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    scrolledWindow.add(chatListView);

    refChatPeep = Gtk::ListStore::create(chatPeep);


    chatListView.append_column("Avatar", chatPeep.avatar);
    chatListView.append_column("ChatEntity Name", chatPeep.chatName);
    chatListView.append_column("", chatPeep.msg_toread);
    chatListView.set_headers_visible(false);

    filter = Gtk::TreeModelFilter::create(refChatPeep);
    filter->set_visible_func(
            [this](const Gtk::TreeModel::const_iterator &iter) -> bool {
                Gtk::TreeModel::Row row = *iter;
                Glib::ustring s = row[chatPeep.chatName];
                s = s.lowercase();
                if (s.find(this->searchEntry.get_text().lowercase()) != Glib::ustring::npos) {
                    return true;
                } else {
                    return false;
                }
    });

    sort = Gtk::TreeModelSort::create(filter);
    sort->set_default_sort_func([this](const Gtk::TreeModel::iterator& a, const Gtk::TreeModel::iterator& b)->int{
         int x = (*a)[chatPeep.sortPriority]-(*b)[chatPeep.sortPriority];
         if(x>0){
             return -1;
         }else if(x==0){
             return 0;
         }else{
             return 1;
         }
    });

    chatListView.set_model(sort);


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
        row[chatPeep.sortPriority]=i*10;

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
