//
// Created by ervinxie on 9/3/19.
//

#include "HistroyMessage.h"

HistroyMessage::HistroyMessage(ChatInfo *c) : chatInfo(c) {
    set_border_width(20);
    set_size_request(400, 400);
    pack_start(searchEntry, Gtk::PACK_SHRINK);
    searchEntry.signal_changed().connect([this]{
        filter->refilter();
    });
    searchEntry.set_placeholder_text("enter to search");

    msgList.set_vexpand(true);
    msgList.set_valign(Gtk::ALIGN_FILL);
    msgList.append_column("Avatar", message.senderAvatar);
    msgList.append_column("Sender", message.senderName);
    msgList.append_column("Content", message.content);
    msgList.append_column("Time", message.msgTime);
    msgList.set_headers_visible(true);

    messages = Gtk::ListStore::create(message);
    filter = Gtk::TreeModelFilter::create(messages);

    msgList.set_model(filter);
    filter->set_visible_func([this](const Gtk::TreeModel::const_iterator &iter) -> bool {
        Gtk::TreeModel::Row row = *iter;
        if((iter->get_value(message.senderName).lowercase()).find(searchEntry.get_text().lowercase())!=Glib::ustring::npos){
            return true;
        }
        if((iter->get_value(message.msgTime).lowercase()).find(searchEntry.get_text().lowercase())!=Glib::ustring::npos){
            return true;
        }
        if((iter->get_value(message.content).lowercase()).find(searchEntry.get_text().lowercase())!=Glib::ustring::npos){
            return true;
        }
        return false;
    });

    scrolledWindow.add(msgList);
    scrolledWindow.set_vexpand(true);
    scrolledWindow.set_valign(Gtk::ALIGN_FILL);
    pack_start(scrolledWindow);

    for(auto m: *c->getMsgList()){
        addMessage(m);
    }
}

void HistroyMessage::addMessage(MessageInfo *msg) {
    auto iter = messages->append();
    iter->set_value(message.content, Glib::ustring(msg->getContent()));
    std::cout<<msg->getCreateTime().getString()<<std::endl;
    iter->set_value(message.msgTime, Glib::ustring(msg->getCreateTime().getString()));
    iter->set_value(message.senderName, Glib::ustring(msg->getSender()->getNickName()));
    iter->set_value(message.senderAvatar, PixMan::TryOrDefaultUserAva(32,msg->getSender()->getAvatarPath(),true,msg->getSender()->getUserId()));
}



