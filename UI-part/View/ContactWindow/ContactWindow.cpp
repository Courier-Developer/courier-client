//
// Created by ervinxie on 8/29/19.
//

#include "../implement.h"

ContactWindow::ContactWindow(MainWindow *mainWindow,
                             std::vector<PacketInfo *> &plist,
                             std::vector<GroupInfo *> &glist) :
        mainWindow(mainWindow),
        contactList(this,plist,glist),
        plist(plist),
        glist(glist) {
    set_border_width(0);

    set_vexpand(true);
    set_hexpand(true);
    set_valign(Gtk::ALIGN_FILL);
    set_halign(Gtk::ALIGN_FILL);

    pack_start(contactList,Gtk::PACK_SHRINK);

    frame.add(*Gtk::manage(new ContactInfo(plist[0]->getUsers()->at(0))));
    frame.set_shadow_type(Gtk::SHADOW_NONE);
    pack_start(frame);
    frame.set_hexpand(true);

    show_all_children();

}

ContactWindow::~ContactWindow() {

}
