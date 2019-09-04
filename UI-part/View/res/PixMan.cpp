//
// Created by ervinxie on 9/3/19.
//

#include "PixMan.h"

Glib::RefPtr<Gdk::Pixbuf> PixMan::TryOrDefaultUserAva(int size, std::string path) {
    Glib::RefPtr<Gdk::Pixbuf> avatar;
    if (path == "")
        avatar = Gdk::Pixbuf::create_from_file("/home/ervinxie/Desktop/courier-client/UI-part/View/res/NoAvatar.png");
    else {
        try {
            avatar = Gdk::Pixbuf::create_from_file(path);
        } catch (...) {
            std::cout << "Avatar Load Failed at" << path << std::endl;
            avatar = Gdk::Pixbuf::create_from_file(
                    "/home/ervinxie/Desktop/courier-client/UI-part/View/res/NoAvatar.png");
        }
    }
    avatar = avatar->scale_simple(size, size, Gdk::INTERP_BILINEAR);
    return avatar;
}

Glib::RefPtr<Gdk::Pixbuf> PixMan::getIcon(std::string name, int size) {
    Glib::RefPtr<Gdk::Pixbuf> re;
    if (name == "message") {
        re = Gdk::Pixbuf::create_from_file("/home/ervinxie/Desktop/courier-client/UI-part/View/res/message.png");
    }
    if (name == "message-fill") {
        re = Gdk::Pixbuf::create_from_file("/home/ervinxie/Desktop/courier-client/UI-part/View/res/message-fill.png");
    }
    if (name == "menu") {
        re = Gdk::Pixbuf::create_from_file("/home/ervinxie/Desktop/courier-client/UI-part/View/res/menu.png");
    }
    if (name == "user") {
        re = Gdk::Pixbuf::create_from_file("/home/ervinxie/Desktop/courier-client/UI-part/View/res/user.png");
    }
    if (name == "addteam") {
        re = Gdk::Pixbuf::create_from_file("/home/ervinxie/Desktop/courier-client/UI-part/View/res/addteam.png");
    }
    if (name == "adduser") {
        re = Gdk::Pixbuf::create_from_file("/home/ervinxie/Desktop/courier-client/UI-part/View/res/adduser.png");
    }
    if (name == "close-circle") {
        re = Gdk::Pixbuf::create_from_file("/home/ervinxie/Desktop/courier-client/UI-part/View/res/close-circle.png");
    }
    if (name == "deleteteam") {
        re = Gdk::Pixbuf::create_from_file("/home/ervinxie/Desktop/courier-client/UI-part/View/res/deleteteam.png");
    }
    if (name == "deletetuser") {
        re = Gdk::Pixbuf::create_from_file("/home/ervinxie/Desktop/courier-client/UI-part/View/res/deleteuser.png");
    }
    if (name == "file-copy") {
        re = Gdk::Pixbuf::create_from_file("/home/ervinxie/Desktop/courier-client/UI-part/View/res/file-copy.png");
    }
    if (name == "smile") {
        re = Gdk::Pixbuf::create_from_file("/home/ervinxie/Desktop/courier-client/UI-part/View/res/smile.png");
    }
    if (name == "team") {
        re = Gdk::Pixbuf::create_from_file("/home/ervinxie/Desktop/courier-client/UI-part/View/res/team.png");
    }
    if (name == "deleteteam") {
        re = Gdk::Pixbuf::create_from_file("/home/ervinxie/Desktop/courier-client/UI-part/View/res/deleteteam.png");
    }
    if (name == "deleteteam") {
        re = Gdk::Pixbuf::create_from_file("/home/ervinxie/Desktop/courier-client/UI-part/View/res/deleteteam.png");
    }else{
        re = Gdk::Pixbuf::create_from_file("/home/ervinxie/Desktop/courier-client/UI-part/View/res/"+name+".png");
    }

    re = re->scale_simple(size, size, Gdk::INTERP_BILINEAR);
    return re;
}

Gtk::Image PixMan::getIconImage(std::string name, int size) {
    return Gtk::Image(getIcon(name, size));
}
