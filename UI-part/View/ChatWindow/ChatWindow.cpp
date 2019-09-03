//
// Created by ervinxie on 8/28/19.
//

#include "../implement.h"
#include "ChatWindow.h"


ChatWindow::ChatWindow(MainWindow *mainWindow,
                       std::vector<ChatInfo *> &clist) :
        mainWindow(mainWindow),
        chatList(this, clist),
        clist(clist) {

    pack_start(chatList, Gtk::PACK_SHRINK);
    frame.set_shadow_type(Gtk::SHADOW_NONE);
    pack_start(frame);
//    pack_start(*Gtk::manage(new Gtk::Label("Chat Window")));

    set_vexpand(true);
    set_hexpand(true);
    changeTo(clist[0]);

    show_all_children();
}

void ChatWindow::changeTo(ChatInfo *c) {
    if(c==nullptr){
        frame.remove();
    }else {

        frame.remove();

        frame.add(*Gtk::manage(new Chatting(this, c)));
        frame.show_all_children();
    }
}


ChatWindow::~ChatWindow() {

}

