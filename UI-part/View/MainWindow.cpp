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
        chatWindow(this, clist),
        contactWindow(this, plist, glist),
        otherWindow(this),
        plist(plist),
        clist(clist),
        glist(glist) {
    get_style_context()->add_class("mainWindow");
    std::cout << "Building Main Window" << std::endl;
    this->app = app;

    set_title("MainWindow");
    set_position(Gtk::WIN_POS_CENTER);
//    set_size_request(500, 500);

    add(box);

    box.pack_start(avatar_button_box,Gtk::PACK_SHRINK);
    avatar.set(PixMan::TryOrDefaultUserAva(64,receiver->me->getAvatarPath()));

    avatar.get_style_context()->add_class("avatar");
    avatar_button_box.pack_start(avatar);
    avatar_button_box.get_style_context()->add_class("mainWindowAvatarButtonBox");

//    chats_bt.set_label("CHAT");
    chats_bt.set_image(*Gtk::manage(new Gtk::Image(PixMan::getIcon("message"))));
    avatar_button_box.pack_start(chats_bt,Gtk::PACK_SHRINK);
    contacts_bt.set_image(*Gtk::manage(new Gtk::Image(PixMan::getIcon("user"))));
    avatar_button_box.pack_start(contacts_bt,Gtk::PACK_SHRINK);
    others_bt.set_image(*Gtk::manage(new Gtk::Image(PixMan::getIcon("appstore"))));
    avatar_button_box.pack_start(others_bt,Gtk::PACK_SHRINK);


    avatar_button_box.set_valign(Gtk::ALIGN_START);
    avatar_button_box.set_halign(Gtk::ALIGN_CENTER);
    avatar_button_box.set_vexpand(true);
    avatar_button_box.set_spacing(10);

    chats_bt.signal_clicked().connect([this] {
        changeWindow(CHATS);
    });


    contacts_bt.signal_clicked().connect([this] {
        changeWindow(CONTACTS);
    });

    others_bt.signal_clicked().connect([this] {
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

void MainWindow::refresh() {
    avatar.set(PixMan::TryOrDefaultUserAva(64,receiver->me->getAvatarPath()));
}

