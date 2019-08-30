//
// Created by ervinxie on 8/28/19.
//

#include "ContactInfo.h"

ContactInfo::ContactInfo(){

    set_valign(Gtk::ALIGN_FILL);
    set_halign(Gtk::ALIGN_FILL);
    set_border_width(10);
    set_row_spacing(10);
    set_column_spacing(10);


    avatar = Gdk::Pixbuf::create_from_file("/home/ervinxie/Downloads/f7074b005cd6a206f6fb94392214c5b6.jpeg");
    avatar = avatar->scale_simple(64,64,Gdk::INTERP_BILINEAR);
    Gtk::Image *avatarImg = Gtk::manage(new Gtk::Image(avatar));


    this->attach(*avatarImg,0,0,1,1);

    this->attach(*Gtk::manage(new Gtk::Label("Nick Name")),1,0,1,1);


//    attach(*(new Gtk::Button("test")),0,0,1,1);
    show_all_children();
}

ContactInfo::~ContactInfo() {

}


