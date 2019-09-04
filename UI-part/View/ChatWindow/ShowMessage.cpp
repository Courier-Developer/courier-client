//
// Created by ervinxie on 9/3/19.
//

#include "../implement.h"
#include "ShowMessage.h"

ShowMessage::ShowMessage(MessageInfo *m, bool showNickName) :
        m(m),
        nickName(m->getSender()->getNickName()),
        content(m->getContent()) {
    set_hexpand(false);
    avatar.set_vexpand(false);
    avatar.set_valign(Gtk::ALIGN_START);
    avatar.set_margin_top(10);
    avatar.set_margin_bottom(10);
    avatar.set_margin_left(10);
    avatar.set_margin_right(10);
    avatar.get_style_context()->add_class("avatar");
    avatar.set(PixMan::TryOrDefaultUserAva(32, m->getSender()->getAvatarPath()));
    if (showNickName) {
        messageBox.pack_start(nickName, Gtk::PACK_SHRINK);
        nickName.set_line_wrap(true);
        nickName.get_style_context()->add_class("messageNickName");
    }
    messageBox.pack_start(message);
    message.pack_start(content);
    content.set_line_wrap(true);


    std::cout<<receiver->me->getNickName()<<std::endl;
    std::cout<<m->getSender()->getUserId()<<" "<<receiver->me->getUserId()<<std::endl;

    if (m->getSender()->getUserId() == receiver->me->getUserId()) {
        content.get_style_context()->add_class("myChatMessage");
        set_halign(Gtk::ALIGN_END);
        pack_end(avatar);
        avatar.set_margin_left(0);
        pack_end(*new Gtk::Image(PixMan::getIcon("receiver",10)));
        nickName.set_halign(Gtk::ALIGN_END);
        pack_end(messageBox);
    } else {
        content.get_style_context()->add_class("otherChatMessage");
        set_halign(Gtk::ALIGN_START);
        pack_start(avatar);
        avatar.set_margin_right(0);
        pack_start(*new Gtk::Image(PixMan::getIcon("sender",10)));
        nickName.set_halign(Gtk::ALIGN_START);
        pack_start(messageBox);

    }
    show_all_children();
}
