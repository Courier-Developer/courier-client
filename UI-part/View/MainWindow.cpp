//
// Created by ervinxie on 8/28/19.
//

#include <iostream>
#include <gtkmm/messagedialog.h>
#include "implement.h"

MainWindow::MainWindow(Glib::RefPtr<Gtk::Application> app):otherWindow(this) {

    std::cout << "Building Main Window" << std::endl;
    this->app = app;

    set_title("MainWindow");
    set_position(Gtk::WIN_POS_CENTER);
//    set_size_request(500, 500);

    add(box);

    box.pack_start(bt_box, false, false);

    auto ava = Gdk::Pixbuf::create_from_file("/home/ervinxie/Downloads/f7074b005cd6a206f6fb94392214c5b6.jpeg");
    ava = ava->scale_simple(64,64,Gdk::INTERP_BILINEAR);
    avatar.set(ava);
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

    chats_bt.signal_clicked().connect(sigc::bind<int>(
            sigc::mem_fun(*this, &MainWindow::on_bt), CHATS));

    contacts_bt.signal_clicked().connect(sigc::bind<int>(
            sigc::mem_fun(*this, &MainWindow::on_bt), CONTACTS));

    others_bt.signal_clicked().connect(sigc::bind<int>(
            sigc::mem_fun(*this, &MainWindow::on_bt), OTHERS));



    windowFrame.add(chatWindow);
    windowFrame.set_border_width(0);
    box.pack_start(windowFrame);
    windowFrame.set_shadow_type(Gtk::SHADOW_NONE);

    show_all_children();
}

MainWindow::~MainWindow() {

}

void MainWindow::on_bt(const int &bt_id) {
    switch (bt_id) {
        case CHATS: {
            std::cout << CHATS << " Chats Button Clicked" << std::endl;
            windowFrame.remove();
            windowFrame.add(chatWindow);
            windowFrame.show_all_children();

            break;
        }
        case CONTACTS: {
            std::cout << CONTACTS << " Contacts Button Clicked" << std::endl;
            windowFrame.remove();
            windowFrame.add(contactWindow);
            windowFrame.show_all_children();

            /*
            Gtk::Dialog dialog;
            dialog.add_button("OK",1);
            dialog.set_title("User Info");
            dialog.get_content_area()->pack_start(*Gtk::manage(new ContactInfo));
            dialog.show_all_children();
            int re = dialog.run();
             */
            break;
        }
        case OTHERS: {
            std::cout << OTHERS << " Others Button Clicked" << std::endl;

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
