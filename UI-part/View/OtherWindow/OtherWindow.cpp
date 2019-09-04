//
// Created by ervinxie on 8/29/19.
//

#include "../implement.h"

OtherWindow::OtherWindow(MainWindow *mainWindow) : myInfo(receiver->me, 128) {
    std::cout<<"OtherWindow Building"<<std::endl;
    this->mainWindow = mainWindow;

    set_border_width(10);
    set_vexpand(true);
    set_hexpand(true);
    set_valign(Gtk::ALIGN_FILL);
    set_halign(Gtk::ALIGN_FILL);

    myInfo.set_halign(Gtk::ALIGN_CENTER);
    pack_start(myInfo, Gtk::PACK_SHRINK);

    pack_start(bt_box, Gtk::PACK_SHRINK);

    bt_box.pack_start(editMyInfo, Gtk::PACK_SHRINK);
    editMyInfo.set_label("Edit My Profile");
    editMyInfo.signal_clicked().connect([this] {
        Gtk::Dialog dialog;
        dialog.set_border_width(10);
        dialog.set_size_request(100, 100);
        dialog.set_title("Edit My Profile");
        Gtk::Image ava(PixMan::TryOrDefaultUserAva(150, receiver->me->getAvatarPath()));
        ava.get_style_context()->add_class("avatar");

        Gtk::Button bt;
        bt.set_label("Choose Avatar");
        bt.signal_clicked().connect([this, &ava] {
            Gtk::FileChooserDialog fileChooserDialog("Choose Avatar", Gtk::FILE_CHOOSER_ACTION_OPEN);

            fileChooserDialog.add_button("OK", 1);
            fileChooserDialog.add_button("Cancel", 0);
            int re = fileChooserDialog.run();
            if (re == 1) {
                std::string filepath = fileChooserDialog.get_filename();
                ava.set(PixMan::TryOrDefaultUserAva(150, filepath));
            }
        });
        Gtk::Entry name, sign;
        name.set_text(receiver->me->getNickName());
        sign.set_text(receiver->me->getSignature());

        dialog.get_content_area()->pack_start(ava, Gtk::PACK_SHRINK);
        dialog.get_content_area()->pack_start(bt, Gtk::PACK_SHRINK);
        dialog.get_content_area()->pack_start(name, Gtk::PACK_SHRINK);
        dialog.get_content_area()->pack_start(sign, Gtk::PACK_SHRINK);
        dialog.add_button("Cancel", 0);
        dialog.add_button("OK", 1);
        dialog.show_all_children();
        int results = dialog.run();
    });


    themeChoose.set_label("Change Theme");
    themeChoose.set_halign(Gtk::ALIGN_CENTER);
    bt_box.pack_start(themeChoose, Gtk::PACK_SHRINK);
    themeChoose.signal_clicked().connect([this] {
        Gtk::Dialog dialog;
        dialog.set_border_width(10);
        dialog.set_size_request(100, 100);
        dialog.set_title("Change Title");

        for (auto s:themeManage->getThemeList()) {
            std::cout << s << std::endl;
            Gtk::Button *bt = new Gtk::Button(s);
            dialog.get_content_area()->pack_start(*bt, Gtk::PACK_SHRINK);
            bt->signal_clicked().connect([s] {
                std::cout << s << " clicked" << std::endl;
                themeManage->changeTheme(s);
            });
        }
        dialog.add_button("OK", 1);
        dialog.show_all_children();
        int results = dialog.run();
    });
    bt_box.set_halign(Gtk::ALIGN_CENTER);

    logOut.set_label("Log Out");
    logOut.signal_clicked().connect([this] {
        LogIn *logIn = new LogIn(this->mainWindow->app);
        this->mainWindow->app->add_window(*logIn);
        logIn->show();
        this->mainWindow->hide();
        this->mainWindow->app->remove_window(*(this->mainWindow));
        delete receiver;
    });
    pack_end(logOut, Gtk::PACK_SHRINK);


    show_all_children();
}

OtherWindow::~OtherWindow() {

}
