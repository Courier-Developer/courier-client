//
// Created by ervinxie on 8/28/19.
//

#include <iostream>
#include <gtkmm/messagedialog.h>
#include "implement.h"
#include "MainWindow.h"


MainWindow::MainWindow(Glib::RefPtr<Gtk::Application> app,
                       std::vector<PacketInfo *> &plist,
                       std::vector<GroupInfo *> &glist,
                       std::vector<ChatInfo *> &clist) :
        chatWindow(this,clist),
        contactWindow(this,plist,glist),
        otherWindow(this),
        plist(plist),
        clist(clist),
        glist(glist){

    std::cout << "Building Main Window" << std::endl;
    this->app = app;

    set_title("MainWindow");
    set_position(Gtk::WIN_POS_CENTER);
//    set_size_request(500, 500);

    add(box);

    box.pack_start(bt_box, false, false);

    auto ava = Gdk::Pixbuf::create_from_file("/home/ervinxie/Downloads/f7074b005cd6a206f6fb94392214c5b6.jpeg");
    ava = ava->scale_simple(64, 64, Gdk::INTERP_BILINEAR);
    avatar.set(ava);
    avatar.get_style_context()->add_class("avatar");
    bt_box.pack_start(avatar);

    chats_bt.set_label("CHAT");
    bt_box.pack_start(chats_bt);
    contacts_bt.set_label("CONT");
    bt_box.pack_start(contacts_bt);
    others_bt.set_label("OTHE");
    bt_box.pack_start(others_bt);


    bt_box.set_valign(Gtk::ALIGN_START);
    bt_box.set_halign(Gtk::ALIGN_CENTER);
    bt_box.set_hexpand(false);
    bt_box.set_vexpand(false);
    bt_box.set_spacing(20);
    bt_box.set_margin_top(10);
    bt_box.set_margin_bottom(10);
    bt_box.set_margin_left(10);
    bt_box.set_margin_right(10);

    chats_bt.signal_clicked().connect([this]{
        changeWindow(CHATS);
    });


    contacts_bt.signal_clicked().connect([this]{
        changeWindow(CONTACTS);
    });

    others_bt.signal_clicked().connect([this]{
        changeWindow(OTHERS);
    });


    windowFrame.add(chatWindow);
    windowFrame.set_border_width(0);
    box.pack_start(windowFrame);
    windowFrame.set_shadow_type(Gtk::SHADOW_NONE);

    show_all_children();
}

MainWindow::~MainWindow() {

}

void MainWindow::changeWindow(int to) {
    switch (to) {
        case CHATS: {
            windowFrame.remove();
            windowFrame.add(chatWindow);
            windowFrame.show_all_children();

            break;
        }
        case CONTACTS: {
            windowFrame.remove();
            windowFrame.add(contactWindow);
            windowFrame.show_all_children();
            break;
        }
        case OTHERS: {
            windowFrame.remove();
            windowFrame.add(otherWindow);
            windowFrame.show_all_children();

            break;
        }
        default: {
            std::cout << "UNKOWN" << std::endl;
            break;
        }
    }
}

