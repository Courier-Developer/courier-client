//
// Created by ervinxie on 8/29/19.
//

#include "../implement.h"
#include <iostream>

Chatting::Chatting(ChatWindow *chatWindow,
                   ChatInfo *c) :
        chatName("ChatEntity"),
        chatWindow(chatWindow),
        c(c) {
    set_size_request(400, 500);

    Gtk::Frame *chatNameFrame = Gtk::manage(new Gtk::Frame);
    Gtk::HBox *chatNameAndDetail = Gtk::manage(new Gtk::HBox);


    chatNameAndDetail->pack_start(chatName, Gtk::PACK_SHRINK);
    chatNameAndDetail->pack_end(chatDetailBt, Gtk::PACK_SHRINK);
    chatDetailBt.set_halign(Gtk::ALIGN_END);
    chatDetailBt.set_image_from_icon_name("format-justify-fill");
    chatDetailBt.signal_clicked().connect([this] {
        Gtk::Dialog dialog;
        if (this->c->getTotype() == 1) {
            dialog.get_content_area()->pack_start(*Gtk::manage(new ContactInfo(this->c->getToUser())),
                                                  Gtk::PACK_SHRINK);
        } else if (this->c->getTotype() == 2) {
            dialog.get_content_area()->pack_start(*Gtk::manage(new GroupContactInfo(this->c->getToGroup())),
                                                  Gtk::PACK_SHRINK);
        }

        dialog.add_button("OK", 0);
        dialog.show_all_children();
        dialog.run();
//        if (this->chatWindow->showingDetail) {
//            contactInfo->hide();
//            this->chatWindow->remove(*contactInfo);
//        }
//        else {
//            this->chatWindow->pack_end(*contactInfo, Gtk::PACK_SHRINK);
//            contactInfo->show();
//        }
//        this->chatWindow->showingDetail = !this->chatWindow->showingDetail;

    });

    cancelBt.set_label("Quit This");
    cancelBt.signal_clicked().connect([this] {
        this->chatWindow->chatList.deleteChat(this->c);
    });
    chatNameAndDetail->pack_end(cancelBt);

    chatNameFrame->add(*chatNameAndDetail);

    chatName.set_padding(10, 10);
    pack_start(*chatNameFrame, Gtk::PACK_SHRINK);


    msgList.set_spacing(10);
    scrolledWindow.add(msgList);
    scrolledWindow.set_vexpand(true);
    scrolledWindow.set_valign(Gtk::ALIGN_FILL);
    pack_start(scrolledWindow);


    pack_start(tools, Gtk::PACK_SHRINK);
    expressionBt.set_image_from_icon_name("face-smile");
    fileBt.set_image_from_icon_name("document-open");
    fileBt.signal_clicked().connect([this] {
        Gtk::FileChooserDialog fileChooserDialog("");
        fileChooserDialog.add_button("OK", 0);
        fileChooserDialog.add_button("Cancel", 1);
        fileChooserDialog.run();
    });
    historyBt.set_label("History");
    historyBt.signal_clicked().connect([this] {
        Gtk::Dialog dialog;
        dialog.set_title("History");
        dialog.get_content_area()->pack_start(*Gtk::manage(new HistroyMessage(this->c)));
        dialog.show_all_children();
        dialog.add_button("OK", 0);
        dialog.run();
    });

    tools.pack_start(expressionBt, Gtk::PACK_SHRINK);
    tools.pack_start(fileBt, Gtk::PACK_SHRINK);
    tools.pack_start(historyBt, Gtk::PACK_SHRINK);


    Gtk::Frame *msgEditFrame = Gtk::manage(new Gtk::Frame);
    msgEditFrame->add(msgEdit);
    msgEditFrame->set_border_width(0);
    pack_start(*msgEditFrame, Gtk::PACK_SHRINK);

    refMsgText = Gtk::TextBuffer::create();
    msgEdit.set_buffer(refMsgText);

    msgEdit.set_size_request(100, 100);
    refMsgText->signal_changed().connect([this] {
//        std::cout<<refMsgText->get_text()<<std::endl;
    });
    msgEdit.set_wrap_mode(Gtk::WRAP_CHAR);
    refMsgText->signal_insert().connect(
            [this](const Gtk::TextBuffer::iterator &it, const Glib::ustring &ustring, int x) {
                if (ustring.length() == 1 && ustring[0] == '\n') {
                    refMsgText->set_text("");

                }
            });

    for (auto m:*c->getMsgList()) {
        addMessage(m);
    }

    show_all_children();
}

Chatting::~Chatting() {

}

void Chatting::addMessage(MessageInfo *m) {
    msgList.pack_start(*Gtk::manage(new ShowMessage(m, true)), Gtk::PACK_SHRINK);
}
