//
// Created by ervinxie on 8/29/19.
//

#include "OtherWindow.h"

OtherWindow::OtherWindow() {
    set_vexpand(true);
    set_hexpand(true);
    set_valign(Gtk::ALIGN_FILL);
    set_halign(Gtk::ALIGN_FILL);

    pack_start(*Gtk::manage(new Gtk::Label("Other Window")));


    show_all_children();
}

OtherWindow::~OtherWindow() {

}
