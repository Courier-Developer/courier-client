//
// Created by ervinxie on 8/29/19.
//

#include "OtherWindow.h"

OtherWindow::OtherWindow() {
    set_border_width(10);

    pack_start(*Gtk::manage(new Gtk::Label("Other Window")));

    set_vexpand(true);
    set_hexpand(true);
    set_valign(Gtk::ALIGN_FILL);
    set_halign(Gtk::ALIGN_FILL);


    show_all_children();
}

OtherWindow::~OtherWindow() {

}
