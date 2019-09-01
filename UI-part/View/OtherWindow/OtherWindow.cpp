//
// Created by ervinxie on 8/29/19.
//

#include "../LogIn.h"

OtherWindow::OtherWindow(MainWindow* mainWindow) :myInfo(128){
    this->mainWindow = mainWindow;

    set_border_width(10);
    set_vexpand(true);
    set_hexpand(true);
    set_valign(Gtk::ALIGN_FILL);
    set_halign(Gtk::ALIGN_FILL);

    myInfo.set_halign(Gtk::ALIGN_CENTER);
    pack_start(myInfo,Gtk::PACK_SHRINK);



    pack_start(bt_box,Gtk::PACK_SHRINK);

    skinChoose.set_label("Change Theme");
    skinChoose.set_halign(Gtk::ALIGN_CENTER);
    bt_box.pack_start(skinChoose,Gtk::PACK_SHRINK);
    bt_box.set_halign(Gtk::ALIGN_CENTER);

    logOut.set_label("Log Out");
    logOut.signal_clicked().connect([this]{
        LogIn *logIn = new LogIn(this->mainWindow->app);
        this->mainWindow->app->add_window(*logIn);
        logIn->show();
        this->mainWindow->hide();
        this->mainWindow->app->remove_window(*(this->mainWindow));
    });
    pack_end(logOut,Gtk::PACK_SHRINK);



    show_all_children();
}

OtherWindow::~OtherWindow() {

}
