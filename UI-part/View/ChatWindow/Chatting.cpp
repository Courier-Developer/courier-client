//
// Created by ervinxie on 8/29/19.
//

#include "Chatting.h"

Chatting::Chatting() :chatName("ChatEntity"){
    set_size_request(300,400);
    Gtk::Frame* chatNameFrame = Gtk::manage(new Gtk::Frame);
    chatNameFrame->add(chatName);
    chatName.set_padding(10,10);
    pack_start(*chatNameFrame, Gtk::PACK_SHRINK);


    msgList.set_vexpand(true);
    msgList.set_valign(Gtk::ALIGN_FILL);
    scrolledWindow.add(msgList);
    scrolledWindow.set_vexpand(true);
    scrolledWindow.set_valign(Gtk::ALIGN_FILL);
    pack_start(scrolledWindow);


    pack_start(tools,Gtk::PACK_SHRINK);
    expressionBt.set_image_from_icon_name("face-smile");

    tools.pack_start(expressionBt,Gtk::PACK_SHRINK);



    Gtk::Frame* msgEditFrame = Gtk::manage(new Gtk::Frame);
    msgEditFrame->add(msgEdit);
    msgEditFrame->set_border_width(0);
    pack_start(*msgEditFrame, Gtk::PACK_SHRINK);

    refMsgText = Gtk::TextBuffer::create();
    msgEdit.set_buffer(refMsgText);




    show_all_children();
}

Chatting::~Chatting() {

}
