//
// Created by ervinxie on 9/4/19.
//

#include "implement.h"
#include "ThemeManage.h"
const std::string local_css="/home/ervinxie/Desktop/courier-client/UI-part/View/css/";
ThemeManage::ThemeManage() {
    styleContext = Gtk::StyleContext::create();
    screen = Gdk::Screen::get_default();
    changeTheme("default");
}
void ThemeManage::changeTheme(std::string theme) {
    cssProvider = Gtk::CssProvider::create();
    cssProvider->load_from_path(local_css+theme+".css");
//    std::cout<<cssProvider->to_string()<<std::endl;
    styleContext->add_provider_for_screen(screen, cssProvider,GTK_STYLE_PROVIDER_PRIORITY_USER);
}

std::vector<std::string> ThemeManage::getThemeList() {
    std::vector<std::string> v;
    v.push_back("default");
    v.push_back("ocean");
    return v;
}


