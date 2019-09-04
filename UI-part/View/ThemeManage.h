//
// Created by ervinxie on 9/4/19.
//

#ifndef COURIER_CLIENT_THEMEMANAGE_H
#define COURIER_CLIENT_THEMEMANAGE_H

#include "SignUp.h"

class ThemeManage {
public:
    ThemeManage();
    void changeTheme(std::string theme);
    Glib::RefPtr<Gtk::StyleContext> styleContext;
    Glib::RefPtr<Gdk::Screen> screen;
    Glib::RefPtr<Gtk::CssProvider> cssProvider;
    std::vector<std::string> getThemeList();
};


#endif //COURIER_CLIENT_THEMEMANAGE_H
