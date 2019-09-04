//
// Created by ervinxie on 9/3/19.
//

#include "PixMan.h"

Glib::RefPtr<Gdk::Pixbuf> PixMan::TryOrDefaultUserAva(int size, std::string path) {
    Glib::RefPtr<Gdk::Pixbuf> avatar;
    if(path=="")
        avatar = Gdk::Pixbuf::create_from_file("/home/ervinxie/Desktop/courier-client/UI-part/View/res/NoAvatar.JPG");
    else {
        try {
            avatar = Gdk::Pixbuf::create_from_file(path);
        } catch (...) {
            std::cout << "Avatar Load Failed at" << path << std::endl;
            avatar = Gdk::Pixbuf::create_from_file("/home/ervinxie/Desktop/courier-client/UI-part/View/res/NoAvatar.JPG");
        }
    }
    avatar = avatar->scale_simple(size, size, Gdk::INTERP_BILINEAR);
    return avatar;
}

Glib::RefPtr<Gdk::Pixbuf> PixMan::getIcon(std::string name,int size) {
    Glib::RefPtr<Gdk::Pixbuf> re;
    if(name=="message"){
        re = Gdk::Pixbuf::create_from_file("/home/ervinxie/Desktop/courier-client/UI-part/View/res/message.png");
    }
    if(name=="message-fill"){
        re = Gdk::Pixbuf::create_from_file("/home/ervinxie/Desktop/courier-client/UI-part/View/res/message-fill.png");
    }
    if(name=="menu"){
        re = Gdk::Pixbuf::create_from_file("/home/ervinxie/Desktop/courier-client/UI-part/View/res/menu.png");
    }
    if(name=="user"){
        re = Gdk::Pixbuf::create_from_file("/home/ervinxie/Desktop/courier-client/UI-part/View/res/user.png");
    }
    if(name=="message"){
        re = Gdk::Pixbuf::create_from_file("/home/ervinxie/Desktop/courier-client/UI-part/View/res/message.png");
    }
    re = re->scale_simple(size, size, Gdk::INTERP_BILINEAR);
    return re;
}

Gtk::Image PixMan::getIconImage(std::string name, int size) {
    return Gtk::Image(getIcon(name,size));
}
