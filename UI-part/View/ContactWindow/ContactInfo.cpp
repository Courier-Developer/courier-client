//
// Created by ervinxie on 8/28/19.
//

#include "../implement.h"
#include "ContactInfo.h"


ContactInfo::ContactInfo(UserInfo *u, int avatarSize, int reduce) : avatarSize(avatarSize), u(u) {

    set_spacing(10);
    set_border_width(10);

    grid.set_valign(Gtk::ALIGN_FILL);
    grid.set_halign(Gtk::ALIGN_FILL);
    grid.set_border_width(10);
    grid.set_row_spacing(10);
    grid.set_column_spacing(10);

    avatar = PixMan::TryOrDefaultUserAva(avatarSize,u->getAvatarPath(),u->getStatus()==0);
    nickName.set_text(u->getNickName());
    nickName.set_line_wrap(true);

    Gtk::Image *avatarImg = Gtk::manage(new Gtk::Image(avatar));
    avatarImg->get_style_context()->add_class("avatar");
    grid.attach(*avatarImg, 0, 0, 1, 1);

    nickName.set_text(u->getNickName());
    grid.attach(nickName, 1, 0, 1, 1);

    pack_start(grid, Gtk::PACK_SHRINK);

    signature.set_text(u->getSignature());
    pack_start(signature, Gtk::PACK_SHRINK);

    if (reduce > 5) {
        goto end;
    }
    if (u->getUserId() != receiver->me->getUserId()) {
        std::cout<<u->getPacket()<<std::endl;
        if (u->getPacket() ==0) {
            addFriend.set_label("Add As Friend");
            addFriend.signal_clicked().connect([this]{
                dealer.addFriend(this->u->getUserId(),[this](std::string suc){
                    if (conn.connected()) {
                        conn.disconnect();
                    }
                    conn = dispatcher.connect([=] {

                        receiver->mainWindow->contactWindow.contactList.addNewFriend(this->u);
                        std::cout<<suc<<std::endl;
                    });
                    dispatcher.emit();
                    },[this](std::string err){
                    std::cout<<err<<std::endl;
                });
            });
            pack_start(addFriend, Gtk::PACK_SHRINK);
        }
        if (u->getPacket() == 0) {
            agreeFriend.set_label("Accept Friend");
            pack_start(agreeFriend, Gtk::PACK_SHRINK);
        }

        if (u->getPacket() != 0) {
            deleteFriend.set_label("Delete Friend");
            pack_end(deleteFriend, Gtk::PACK_SHRINK);
        }
    }

    if (reduce > 0) {
        goto end;
    }

    if (u->getPacket() != 0) {
        pack_start(packetCombo, Gtk::PACK_SHRINK);
    }
    refListStore = Gtk::ListStore::create(packetColumn);
    packetCombo.set_model(refListStore);
    packetCombo.pack_start(packetColumn.name);
    for (auto p : receiver->plist) {
        if (p->getPriority() != 0) {
            auto iter = refListStore->append();
            p_iter[p] = iter;
            iter->set_value(packetColumn.name, Glib::ustring(p->getName()));
            iter->set_value(packetColumn.p, p);
            if (p->getPacketId() == u->getPacket()) {
                packetCombo.set_active(iter);
            }
        }
    }
    packetCombo.signal_changed().connect([this] {
        if (dialoging == false) {
            dialoging = true;
            auto pa = packetCombo.get_active()->get_value(packetColumn.p);
            Gtk::Dialog dialog;
            dialog.set_border_width(10);
            dialog.set_size_request(100, 100);
            Glib::ustring info = "Change " + Glib::ustring(this->u->getNickName()) + " to Group[" + pa->getName() + "]";
            Gtk::Label *label = Gtk::manage(new Gtk::Label(info));
            label->set_line_wrap(true);
            dialog.get_content_area()->pack_start(*label);
            dialog.add_button("Cancel", 0);
            dialog.add_button("OK", 1);
            dialog.show_all_children();
            if (dialog.run() == 1) {
                dealer.moveToPacket(this->u,pa,[this](std::string s){
                    std::cout<<s<<std::endl;
                },[this](std::string erro){
                    std::cout<<erro<<std::endl;
                });
            } else {
                auto iter = p_iter[this->u->getInPacket()];
                packetCombo.set_active(p_iter[this->u->getInPacket()]);

            }
            dialoging = false;
        }

    });
    if (u->getUserId() != receiver->me->getUserId()) {
        startChat.set_label("Start Chat");
        startChat.signal_clicked().connect([this] {
            auto c = this->u->getChat();
            receiver->mainWindow->changeWindow(CHATS);
            receiver->mainWindow->chatWindow.chatList.addChat(c);
            receiver->mainWindow->chatWindow.changeTo(c);
        });
        pack_start(startChat, Gtk::PACK_SHRINK);
    }


    end:
    show_all_children();
}

ContactInfo::~ContactInfo() {
    hide();
}






