//
// Created by ervinxie on 8/28/19.
//

#ifndef GTKMM_CHATWINDOW_H
#define GTKMM_CHATWINDOW_H


#include <gtkmm.h>
#include "ChatList.h"
#include "Chatting.h"

class ChatWindow : public Gtk::HBox{
public:
    ChatWindow();
    virtual ~ChatWindow();

protected:
    ChatList chatList;
    Chatting chatting;
};


#endif //GTKMM_CHATWINDOW_H
