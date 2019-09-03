//
// Created by ervinxie on 8/29/19.
//

#include <iostream>
#include "../implement.h"
#include "ChatList.h"


ChatList::ChatList(ChatWindow *chatWindow,
                   std::vector<ChatInfo *> &clist) :
        chatWindow(chatWindow),
        clist(clist) {

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
    chatListView.append_column("Unread",chatPeep.msg_toread);
    chatListView.set_headers_visible(false);


    filter = Gtk::TreeModelFilter::create(refChatPeep);
    filter->set_visible_func([this](const Gtk::TreeModel::const_iterator &iter) -> bool {
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
    sort->set_default_sort_func([this](const Gtk::TreeModel::iterator &a, const Gtk::TreeModel::iterator &b) -> int {
        int x = (*a)[chatPeep.sortPriority] - (*b)[chatPeep.sortPriority];
        if (x > 0) {
            return -1;
        } else if (x == 0) {
            return 0;
        } else {
            return 1;
        }
    });

    chatListView.set_model(sort);

    select = chatListView.get_selection();

    select->signal_changed().connect([this]{
        Gtk::TreeModel::iterator iter = select->get_selected();
        if (iter) {
            Gtk::TreeModel::Row row = *iter;
            std::cout << "The " << row[chatPeep.chatName] << " " << row[chatPeep.msg_toread] << " Clicked. " << std::endl;
            this->chatWindow->changeTo(iter->get_value(chatPeep.c));
        }
    });

    for(auto c:clist){
        addChat(c);
    }

    show_all_children();
}

void ChatList::addChat(ChatInfo *newChat) {
    if(c_iter.count(newChat)==0) {
        auto iter = refChatPeep->append();
        iter->set_value(chatPeep.type, newChat->getTotype());
        Glib::RefPtr<Gdk::Pixbuf> ava;
        if (newChat->getTotype() == 1) {
            iter->set_value(chatPeep.chatName, Glib::ustring(newChat->getToUser()->getNickName()));
            iter->set_value(chatPeep.avatar, PixMan::TryOrDefaultUserAva(64, newChat->getToUser()->getAvatarPath()));
        } else if (newChat->getTotype() == 2) {
            iter->set_value(chatPeep.chatName, Glib::ustring(newChat->getToGroup()->getNickName()));
            iter->set_value(chatPeep.avatar, PixMan::TryOrDefaultUserAva(64, newChat->getToGroup()->getAvatarPath()));
        }
        iter->set_value(chatPeep.c, newChat);
        c_iter[newChat] = iter;
        iter->set_value(chatPeep.msg_toread, newChat->getUnreadNumbers());

    }else{
        this->chatWindow->changeTo(newChat);
    }
}

void ChatList::deleteChat(ChatInfo* c) {
    auto iter = c_iter[c];
    refChatPeep->erase(iter);
    c_iter.erase(c);
    chatWindow->changeTo(nullptr);
}


ChatList::~ChatList() {

}


