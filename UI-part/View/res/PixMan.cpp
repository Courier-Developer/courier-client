//
// Created by ervinxie on 9/3/19.
//

#include "PixMan.h"

Glib::RefPtr<Gdk::Pixbuf> PixMan::TryOrDefaultUserAva(int size, std::string path) {
    Glib::RefPtr<Gdk::Pixbuf> avatar;
    if(path=="")
        avatar = Gdk::Pixbuf::create_from_file("/home/ervinxie/Downloads/f7074b005cd6a206f6fb94392214c5b6.jpeg");
    else {
        try {
            avatar = Gdk::Pixbuf::create_from_file(path);
        } catch (...) {
            std::cout << "Avatar Load Failed at" << path << std::endl;
            avatar = Gdk::Pixbuf::create_from_file("/home/ervinxie/Downloads/f7074b005cd6a206f6fb94392214c5b6.jpeg");
        }
    }
    avatar = avatar->scale_simple(size, size, Gdk::INTERP_BILINEAR);
    return avatar;
}
