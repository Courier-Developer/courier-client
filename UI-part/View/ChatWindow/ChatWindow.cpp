//
// Created by ervinxie on 8/28/19.
//

#include "ChatWindow.h"

ChatWindow::ChatWindow() {

    pack_start(chatList, Gtk::PACK_SHRINK);
    pack_start(chatting);

    set_vexpand(true);
    set_hexpand(true);


    show_all_children();
}

ChatWindow::~ChatWindow() {

}
