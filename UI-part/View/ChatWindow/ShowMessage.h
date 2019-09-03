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
    Gtk::Label nickName,content;
    Gtk::VBox messageBox;
};


#endif //COURIER_CLIENT_SHOWMESSAGE_H
