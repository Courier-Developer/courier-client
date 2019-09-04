//
// Created by ervinxie on 9/3/19.
//

#ifndef COURIER_CLIENT_PIXMAN_H
#define COURIER_CLIENT_PIXMAN_H

#include <gtkmm.h>
#include <iostream>
class PixMan {
public:
    static Glib::RefPtr<Gdk::Pixbuf> TryOrDefaultUserAva(int size=64,std::string path="");

};


#endif //COURIER_CLIENT_PIXMAN_H
