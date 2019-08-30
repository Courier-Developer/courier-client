//
// Created by ervinxie on 8/29/19.
//

#include "Chatting.h"

Chatting::Chatting() :chatName("Chat"){
    pack_start(chatName,Gtk::PACK_SHRINK);

    msgList.set_vexpand(true);
    msgList.set_valign(Gtk::ALIGN_FILL);
    scrolledWindow.add(msgList);
    scrolledWindow.set_vexpand(true);
    scrolledWindow.set_valign(Gtk::ALIGN_FILL);


    pack_start(scrolledWindow);


    pack_start(toolbar,Gtk::PACK_SHRINK);
    pack_start(*Gtk::manage(new Gtk::Label("ToolBar")));
    pack_start(msgEdit, Gtk::PACK_SHRINK);
    refMsgText = Gtk::TextBuffer::create();
    msgEdit.set_buffer(refMsgText);



    show_all_children();
}

Chatting::~Chatting() {

}
