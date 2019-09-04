//
// Created by ervinxie on 9/4/19.
//

#include "PacketContactInfo.h"

PacketContactInfo::PacketContactInfo(PacketInfo *p) : p(p) {
    if (p == nullptr) {
        label.set_text("Group of Groups");
    } else {
        label.set_text(p->getName());
    }
    pack_start(label, Gtk::PACK_SHRINK);
    pack_end(deleteBt, Gtk::PACK_SHRINK);

    if(p!=nullptr) {
        deleteBt.set_label("Delete This Group");
        deleteBt.signal_clicked().connect([this] {
            Gtk::Dialog dialog;
            dialog.set_border_width(10);
            dialog.set_size_request(100, 100);
            if (this->p->getUsers()->size() == 0) {
                Glib::ustring info = "Confirm Delete This User Classification?";
                Gtk::Label *label = Gtk::manage(new Gtk::Label(info));
                label->set_line_wrap(true);
                dialog.get_content_area()->pack_start(*label);
                dialog.add_button("Cancel", 0);
                dialog.add_button("Confirm", 1);
                int results = dialog.run();
                if (results == 1) {

                } else if (results == 0) {

                }
            } else {
                Glib::ustring info = "You cannot delete this classification because of remaining users!";
                Gtk::Label *label = Gtk::manage(new Gtk::Label(info));
                label->set_line_wrap(true);
                dialog.get_content_area()->pack_start(*label);
                dialog.add_button("OK", 0);
            }
            dialog.show_all_children();
        });
    }
    show_all_children();
}
