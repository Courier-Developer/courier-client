//
// Created by ervinxie on 9/3/19.
//

#ifndef COURIER_CLIENT_SHOWMESSAGE_H
#define COURIER_CLIENT_SHOWMESSAGE_H

#include "HistroyMessage.h"
class ShowMessage : public Gtk::HBox{
public:
    ShowMessage(MessageInfo* m,bool showNickName= false);
    MessageInfo* m;
    Gtk::Image avatar;
    Gtk::VBox message;
    Gtk::Label nickName,textContent;
    Gtk::VBox messageBox;
    Gtk::Spinner loading;
    Glib::Dispatcher dispatcher;
    sigc::connection conn;
    void toggle();
};


#endif //COURIER_CLIENT_SHOWMESSAGE_H
