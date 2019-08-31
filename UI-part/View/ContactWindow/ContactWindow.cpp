//
// Created by ervinxie on 8/29/19.
//

#include "ContactWindow.h"

ContactWindow::ContactWindow() {
    set_border_width(0);

    set_vexpand(true);
    set_hexpand(true);
    set_valign(Gtk::ALIGN_FILL);
    set_halign(Gtk::ALIGN_FILL);

    pack_start(contactList);


    show_all_children();
}

ContactWindow::~ContactWindow() {

}
