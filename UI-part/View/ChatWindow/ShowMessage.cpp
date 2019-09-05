//
// Created by ervinxie on 9/3/19.
//

#include "../implement.h"

ShowMessage::ShowMessage(MessageInfo *m, bool showNickName) :
        m(m),
        nickName(m->getSender()->getNickName()),
        textContent(m->getContent()) {
    std::cout<<"Constructing Messsage"<<std::endl;
    set_hexpand(false);
    avatar.set_vexpand(false);
    avatar.set_valign(Gtk::ALIGN_START);
    avatar.set_margin_top(10);
    avatar.set_margin_bottom(10);
    avatar.set_margin_left(10);
    avatar.set_margin_right(10);
    avatar.get_style_context()->add_class("avatar");
    avatar.set(PixMan::TryOrDefaultUserAva(32, m->getSender()->getAvatarPath(),true,m->getSender()->getUserId()));
    if (showNickName) {
        messageBox.pack_start(nickName, Gtk::PACK_SHRINK);
        nickName.set_line_wrap(true);
        nickName.get_style_context()->add_class("messageNickName");
    }

    messageBox.pack_start(message);
    textContent.set_text(m->getContent());
    std::cout<<"msg kind"<<m->getContentKind()<<std::endl;
    if(m->getContentKind()==1){
        message.pack_start(textContent);
    }else if(m->getContentKind()==2){
        message.pack_start(*Gtk::manage(new Gtk::Image(PixMan::getIcon("file-copy",64))));
        message.pack_start(textContent);
    }else if(m->getContentKind()==3){
        message.pack_start(*Gtk::manage(new Gtk::Image(PixMan::getPic(m->getContent()))));
    }



    textContent.set_line_wrap(true);


    std::cout<<"Constructing Messsage"<<std::endl;

    std::cout<<receiver->me->getNickName()<<std::endl;
    std::cout<<m->getSender()->getUserId()<<" "<<receiver->me->getUserId()<<std::endl;


    if (m->getSender()->getUserId() == receiver->me->getUserId()) {
        textContent.get_style_context()->add_class("myChatMessage");
        set_halign(Gtk::ALIGN_END);
        pack_end(avatar);
        avatar.set_margin_left(0);
        auto rec=new Gtk::Image(PixMan::getIcon("receiver",10));
        rec->set_valign(Gtk::ALIGN_START);
        rec->set_margin_top(20);
        pack_end(*rec);
        nickName.set_halign(Gtk::ALIGN_END);
        pack_end(messageBox);
        pack_end(loading);
    } else {
        textContent.get_style_context()->add_class("otherChatMessage");
        set_halign(Gtk::ALIGN_START);
        pack_start(avatar);
        avatar.set_margin_right(0);
        auto sen = new Gtk::Image(PixMan::getIcon("sender",10));
        sen->set_valign(Gtk::ALIGN_START);
        sen->set_margin_top(20);
        pack_start(*sen);
        nickName.set_halign(Gtk::ALIGN_START);
        pack_start(messageBox);
        pack_start(loading);
    }
    if(m->getSenderId()==receiver->me->getUserId()) {
        loading.property_active() = true;
        dispatcher.connect([this]{
            this->loading.property_active() = ! this->loading.property_active();
        });
    }
    show_all_children();


}

void ShowMessage::toggle() {
    dispatcher.emit();
}
