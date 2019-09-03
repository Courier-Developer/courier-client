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
    set_spacing(10);
    avatar.set_vexpand(false);
    avatar.set_valign(Gtk::ALIGN_START);
    avatar.set_margin_top(10);
    avatar.set_margin_bottom(10);
    avatar.set_margin_left(10);
    avatar.set_margin_right(10);
    avatar.set(PixMan::TryOrDefaultUserAva(32, m->getSender()->getAvatarPath()));
    if (showNickName) {
        messageBox.pack_start(nickName, Gtk::PACK_SHRINK);
    }
    messageBox.pack_start(message);
    message.pack_start(content);
    content.get_style_context()->add_class("ChatMessage");

    if (m->getSender()->getUserId() == receiver->me.getUserId()) {
        set_halign(Gtk::ALIGN_END);
        pack_end(avatar);
        nickName.set_halign(Gtk::ALIGN_END);
        pack_end(messageBox);
    } else {
        set_halign(Gtk::ALIGN_START);
        pack_start(avatar);
        nickName.set_halign(Gtk::ALIGN_START);
        pack_start(messageBox);

    }
    show_all_children();
}
