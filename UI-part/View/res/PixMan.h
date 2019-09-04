//
// Created by ervinxie on 9/3/19.
//

#ifndef COURIER_CLIENT_PIXMAN_H
#define COURIER_CLIENT_PIXMAN_H

#include <gtkmm.h>
#include <iostream>
class PixMan {
public:
    static Glib::RefPtr<Gdk::Pixbuf> TryOrDefaultUserAva(int size=64,std::string path="",bool isgray=false);
    static Glib::RefPtr<Gdk::Pixbuf> getIcon(std::string name,int size=40);
    static Gtk::Image getIconImage(std::string name,int size=40);
    static Glib::RefPtr<Gdk::Pixbuf> getPic(std::string name,int width=150);
};


#endif //COURIER_CLIENT_PIXMAN_H
