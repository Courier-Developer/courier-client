//
// Created by ervinxie on 8/28/19.
//

#ifndef GTKMM_CHATWINDOW_H
#define GTKMM_CHATWINDOW_H


#include <gtkmm.h>
#include "Chatting.h"

class ChatWindow : public Gtk::HBox {
public:
    ChatWindow(MainWindow *mainWindow, std::vector<ChatInfo *> &clist);

    virtual ~ChatWindow();

    MainWindow *mainWindow;
    std::vector<ChatInfo *> &clist;
    std::map<ChatInfo *, Chatting *> c_ui;
    void changeTo(ChatInfo* c);
protected:
    ChatList chatList;
    Gtk::Frame frame;
};


#endif //GTKMM_CHATWINDOW_H
