//
// Created by ervinxie on 8/28/19.
//

#include "../implement.h"

ChatWindow::ChatWindow(MainWindow *mainWindow,
                       std::vector<ChatInfo *> &clist) :
        mainWindow(mainWindow),
        chatList(this,clist),
        chatting(this,clist[0]),
        clist(clist) {

    pack_start(chatList, Gtk::PACK_SHRINK);
    pack_start(chatting);
//    pack_start(*Gtk::manage(new Gtk::Label("Chat Window")));

    set_vexpand(true);
    set_hexpand(true);

    show_all_children();
}

ChatWindow::~ChatWindow() {

}
