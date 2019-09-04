#include<gtkmm-3.0/gtkmm.h>

#include "View/implement.h"
#include <iostream>
#include <thread>
#include <mutex>
Dealer dealer;
int main(int argc, char *argv[])
{
    tm *local;
    time_t t;
    t = time(NULL);
    local = localtime(&t);
    MessageInfo *tmp;
    DateTime sendtime("2019-8-31 21:23:54");
    std::cout<<sendtime.getString()<<std::endl;

    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv,"com.courier");
    LogIn logIn(app);

    Glib::RefPtr<Gtk::CssProvider> cssProvider = Gtk::CssProvider::create();
    cssProvider->load_from_path("/home/ervinxie/Desktop/courier-client/UI-part/View/style.css");
    std::cout<<cssProvider->to_string()<<std::endl;

    Glib::RefPtr<Gtk::StyleContext> styleContext = Gtk::StyleContext::create();
//get default screen
    Glib::RefPtr<Gdk::Screen> screen = Gdk::Screen::get_default();
    logIn.get_property("screen",screen);

    std::cout<<logIn.get_style_context()->get_background_color().to_string()<<std::endl;

    styleContext->add_provider_for_screen(screen, cssProvider,GTK_STYLE_PROVIDER_PRIORITY_USER);

    return app->run(logIn);
}