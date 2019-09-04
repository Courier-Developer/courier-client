#include<gtkmm-3.0/gtkmm.h>

#include "View/implement.h"

Dealer dealer;
ThemeManage* themeManage;
int main(int argc, char *argv[])
{

    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv,"com.courier");
    LogIn logIn(app);

    themeManage = new ThemeManage;


    return app->run(logIn);
}