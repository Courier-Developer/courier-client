//
// Created by ervinxie on 8/28/19.
//

#include "MainWindow.h"
#include <iostream>
#include <gtkmm/messagedialog.h>
#include "ContactWindow/ContactInfo.h"

MainWindow::MainWindow() : chats_bt("Chats"),
                           contacts_bt("Contacts"),
                           others_bt("Others"),
                           bt_box(Gtk::ORIENTATION_VERTICAL) {

    std::cout << "Building Main Window" << std::endl;

    set_title("MainWindow");
    set_position(Gtk::WIN_POS_CENTER);
//    set_size_request(500, 500);

    add(box);

    box.pack_start(bt_box, false, false);

    bt_box.pack_start(chats_bt);
    bt_box.pack_start(contacts_bt);
    bt_box.pack_start(others_bt);

    bt_box.set_valign(Gtk::ALIGN_CENTER);
    bt_box.set_halign(Gtk::ALIGN_CENTER);
    bt_box.set_hexpand(false);
    bt_box.set_vexpand(false);

    chats_bt.signal_clicked().connect(sigc::bind<int>(
            sigc::mem_fun(*this, &MainWindow::on_bt), CHATS));

    contacts_bt.signal_clicked().connect(sigc::bind<int>(
            sigc::mem_fun(*this, &MainWindow::on_bt), CONTACTS));

    others_bt.signal_clicked().connect(sigc::bind<int>(
            sigc::mem_fun(*this, &MainWindow::on_bt), OTHERS));


    now_on = CHATS;
    box.pack_start(chatWindow);





    show_all_children();
}

MainWindow::~MainWindow() {

}

void MainWindow::on_bt(const int &bt_id) {
    switch (bt_id) {
        case CHATS: {
            std::cout << CHATS << " Chats Button Clicked" << std::endl;
            if (now_on == CONTACTS) {
                box.remove(contactWindow);
            } else if (now_on == OTHERS) {
                box.remove(otherWindow);
            }
            if (now_on != CHATS) {
                box.pack_start(chatWindow);
                now_on = CHATS;
                box.show_all_children();
            }

            break;
        }
        case CONTACTS: {
            std::cout << CONTACTS << " Contacts Button Clicked" << std::endl;

            if (now_on == CHATS) {
                box.remove(chatWindow);
            } else if (now_on == OTHERS) {
                box.remove(otherWindow);
            }
            if (now_on != CONTACTS) {
                box.pack_start(contactWindow);
                now_on = CONTACTS;
                box.show_all_children();
            }
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

            if (now_on == CONTACTS) {
                box.remove(contactWindow);
            } else if (now_on == CHATS) {
                box.remove(chatWindow);
            }
            if (now_on != OTHERS) {
                box.pack_start(otherWindow);
                now_on = OTHERS;
                box.show_all_children();
            }
            break;
        }
        default: {
            std::cout << "UNKOWN" << std::endl;
            break;
        }
    }
}
