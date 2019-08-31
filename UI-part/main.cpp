#include<gtkmm-3.0/gtkmm.h>

#include "View/LogIn.h"

int main(int argc, char *argv[])
{
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv,"com.courier");

    LogIn logIn(app);

    return app->run(logIn);
}