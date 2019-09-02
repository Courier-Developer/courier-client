//
// Created by ervinxie on 8/28/19.
//

#include "../implement.h"

ContactInfo::ContactInfo(int avatarSize){
    this->avatarSize = avatarSize;
    set_valign(Gtk::ALIGN_FILL);
    set_halign(Gtk::ALIGN_FILL);
    set_border_width(10);
    set_row_spacing(10);
    set_column_spacing(10);

    avatar = Gdk::Pixbuf::create_from_file("/home/ervinxie/Downloads/f7074b005cd6a206f6fb94392214c5b6.jpeg");

    avatar = avatar->scale_simple(avatarSize,avatarSize,Gdk::INTERP_BILINEAR);
    Gtk::Image *avatarImg = Gtk::manage(new Gtk::Image(avatar));

    this->attach(*avatarImg,0,0,1,1);

    nickName.set_text("Nick Name");
    this->attach(nickName,1,0,1,1);


//    attach(*(new Gtk::Button("test")),0,0,1,1);
    show_all_children();
}
ContactInfo::ContactInfo(UserInfo *userInfo,int avatarSize) {
    this->avatarSize=avatarSize;
    ContactInfo();
    ChangeUser(userInfo);

}


ContactInfo::~ContactInfo() {
    hide();
}


void ContactInfo::ChangeUser(UserInfo *newUser) {
    avatar = Gdk::Pixbuf::create_from_file(newUser->getAvatarPath());
    avatar = avatar->scale_simple(avatarSize,avatarSize,Gdk::INTERP_BILINEAR);
    nickName.set_text(newUser->getNickName());


}


