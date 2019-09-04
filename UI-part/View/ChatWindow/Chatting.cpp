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
    chatDetailBt.set_image(*Gtk::manage(new Gtk::Image(PixMan::getIcon("menu",20))));
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

    cancelBt.set_image(*Gtk::manage(new Gtk::Image(PixMan::getIcon("close-circle",20))));
    cancelBt.signal_clicked().connect([this] {
        this->chatWindow->chatList.deleteChat(this->c);
    });
    chatNameAndDetail->pack_end(cancelBt,Gtk::PACK_SHRINK);

    chatNameFrame->add(*chatNameAndDetail);

    chatName.set_padding(10, 10);
    pack_start(*chatNameFrame, Gtk::PACK_SHRINK);


    msgList.set_spacing(10);
    scrolledWindow.add(msgList);
    scrolledWindow.set_vexpand(true);
    scrolledWindow.set_valign(Gtk::ALIGN_FILL);
    pack_start(scrolledWindow);


    pack_start(tools, Gtk::PACK_SHRINK);
    tools.get_style_context()->add_class("tools");


    Glib::ustring emoji;
    std::ifstream fin("emoji.txt");
    fin>>emoji;
    std::cout<<emoji<<std::endl;
    expressionBt.set_image(*Gtk::manage(new Gtk::Image(PixMan::getIcon("smile",20))));
    expressionBt.signal_clicked().connect([=]{
        Gtk::Dialog dialog;
        Gtk::Label label(emoji);
        label.set_line_wrap(true);
        dialog.get_content_area()->pack_start(label);
        dialog.show_all_children();
        int re=dialog.run();
    });

    imageBt.set_image(*Gtk::manage(new Gtk::Image(PixMan::getIcon("image",20))));
    imageBt.signal_clicked().connect([this]{
        Gtk::FileChooserDialog fileChooserDialog("Choose an image to send");
        fileChooserDialog.add_button("OK", 1);
        fileChooserDialog.add_button("Cancel", 0);
        int re = fileChooserDialog.run();
        if(re==1){
            auto nm = dealer.newMessage(3,fileChooserDialog.get_filename(),this->c);
            std::cout<<"nm:"<<nm->getContentKind()<<std::endl;
            auto sm=addMessage(nm);
            dealer.sendMessage(nm,[this,sm](std::string s){
                std::cout<<s<<std::endl;
                sm->toggle();

            },[this,sm](std::string s){
                std::cout<<s<<std::endl;
                sm->toggle();
            });
        }
    });

    fileBt.set_image(*Gtk::manage(new Gtk::Image(PixMan::getIcon("file-copy",20))));
    fileBt.signal_clicked().connect([this] {
        Gtk::FileChooserDialog fileChooserDialog("Choose a File to Send");
        fileChooserDialog.add_button("OK", 1);
        fileChooserDialog.add_button("Cancel", 0);
        int re=fileChooserDialog.run();
        if(re==1){
            auto nm = dealer.newMessage(2,fileChooserDialog.get_filename(),this->c);
            std::cout<<"nm:"<<nm->getContentKind()<<std::endl;
            auto sm=addMessage(nm);
            dealer.sendMessage(nm,[this,sm](std::string s){
                std::cout<<s<<std::endl;
                sm->toggle();
            },[this,sm](std::string s){
                std::cout<<s<<std::endl;
                sm->toggle();
            });
        }

    });
    historyBt.set_image(*Gtk::manage(new Gtk::Image(PixMan::getIcon("database",20))));
    historyBt.signal_clicked().connect([this] {
        Gtk::Dialog dialog;
        dialog.set_title("History");
        dialog.get_content_area()->pack_start(*Gtk::manage(new HistroyMessage(this->c)));
        dialog.show_all_children();
        dialog.add_button("OK", 0);
        dialog.run();
    });

    tools.pack_start(expressionBt, Gtk::PACK_SHRINK);
    tools.pack_start(imageBt,Gtk::PACK_SHRINK);
    tools.pack_start(fileBt, Gtk::PACK_SHRINK);
    tools.pack_start(historyBt, Gtk::PACK_SHRINK);


    Gtk::Frame *msgEditFrame = Gtk::manage(new Gtk::Frame);
    msgEditFrame->add(msgEdit);
    msgEditFrame->set_border_width(0);
    pack_start(*msgEditFrame, Gtk::PACK_SHRINK);

    refMsgText = Gtk::TextBuffer::create();
    msgEdit.set_buffer(refMsgText);
    msgEditFrame->get_style_context()->add_class("msgEditFrame");
    msgEdit.get_style_context()->add_class("msgEdit");


    msgEdit.set_size_request(100, 100);
    refMsgText->signal_changed().connect([this] {
//        std::cout<<refMsgText->get_text()<<std::endl;
    });
    msgEdit.set_wrap_mode(Gtk::WRAP_CHAR);
    refMsgText->signal_insert().connect(
            [this](const Gtk::TextBuffer::iterator &it, const Glib::ustring &ustring, int x) {
                if (ustring.length() == 1 && ustring[0] == '\n') {

                    auto nm = dealer.newMessage(1,refMsgText->get_text().substr(0,refMsgText->get_text().length()-1),this->c);
                    std::cout<<"nm:"<<nm->getContentKind()<<std::endl;
                    auto sm = addMessage(nm);
                    dealer.sendMessage(nm,[this,sm](std::string s){
                        std::cout<<s<<std::endl;
                        sm->toggle();
                    },[this,sm](std::string s){
                        std::cout<<s<<std::endl;
                        sm->toggle();
                    });
                    refMsgText->set_text("");

                }
            });

    for (auto m:*c->getMsgList()) {
        auto sm= addMessage(m);
        sm->toggle();
    }

    show_all_children();
}

Chatting::~Chatting() {

}

ShowMessage* Chatting::addMessage(MessageInfo *m) {

    std::cout<<"Chatting adding Messsage"<<std::endl;
    std::cout<<m<<std::endl;
    std::cout<<m->getSender()<<std::endl;
    std::cout<<m->getContent()<<std::endl;
    std::cout<<m->getSender()->getNickName()<<std::endl;
    auto sm = Gtk::manage(new ShowMessage(m, true));
    msgList.pack_start(*sm, Gtk::PACK_SHRINK);
    msgList.show_all_children();
    auto adj = scrolledWindow.get_vadjustment();
    adj->set_value(adj->get_upper());
    std::cout<<adj->get_upper()<<std::endl;
    return sm;
}
