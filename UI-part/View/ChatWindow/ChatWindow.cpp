//
// Created by ervinxie on 8/28/19.
//

#include "ChatWindow.h"

ChatWindow::ChatWindow() {
    set_border_width(10);

    pack_start(*Gtk::manage(new Gtk::Label("Chat Window")));

    pack_start(chatList);
    pack_start(chatting);

    set_vexpand(true);
    set_hexpand(true);



    show_all_children();

}

ChatWindow::~ChatWindow() {

}
