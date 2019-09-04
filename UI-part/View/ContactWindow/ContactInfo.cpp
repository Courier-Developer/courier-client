//
// Created by ervinxie on 8/28/19.
//

#include "../implement.h"

ContactInfo::ContactInfo(UserInfo *u, int avatarSize, int reduce) : avatarSize(avatarSize), u(u) {

    set_spacing(10);
    set_border_width(10);

    grid.set_valign(Gtk::ALIGN_FILL);
    grid.set_halign(Gtk::ALIGN_FILL);
    grid.set_border_width(10);
    grid.set_row_spacing(10);
    grid.set_column_spacing(10);

    avatar = Gdk::Pixbuf::create_from_file("/home/ervinxie/Downloads/f7074b005cd6a206f6fb94392214c5b6.jpeg");
    avatar = avatar->scale_simple(avatarSize, avatarSize, Gdk::INTERP_BILINEAR);

    try {
        avatar = Gdk::Pixbuf::create_from_file(u->getAvatarPath());
    } catch (...) {
        std::cout << u->getNickName() << ":ContactInfo Avatar Load Failed at" << u->getAvatarPath()
                  << std::endl;
        avatar = Gdk::Pixbuf::create_from_file("/home/ervinxie/Downloads/f7074b005cd6a206f6fb94392214c5b6.jpeg");
    }
    avatar = avatar->scale_simple(avatarSize, avatarSize, Gdk::INTERP_BILINEAR);
    nickName.set_text(u->getNickName());
    nickName.set_line_wrap(true);

    Gtk::Image *avatarImg = Gtk::manage(new Gtk::Image(avatar));
    grid.attach(*avatarImg, 0, 0, 1, 1);

    nickName.set_text(u->getNickName());
    grid.attach(nickName, 1, 0, 1, 1);

    pack_start(grid, Gtk::PACK_SHRINK);

    signature.set_text(u->getSignature());
    pack_start(signature, Gtk::PACK_SHRINK);

    if (reduce > 5) {
        goto end;
    }

    if (u->getPacket() == 0) {
        addFriend.set_label("Add As Friend");
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

    if(reduce>0){
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

            } else {
                auto iter = p_iter[this->u->getInPacket()];
                packetCombo.set_active(p_iter[this->u->getInPacket()]);

            }
            dialoging = false;
        }

    });

    startChat.set_label("Start Chat");
    startChat.signal_clicked().connect([this] {
        auto c = this->u->getChat();
        receiver->mainWindow->changeWindow(CHATS);
        receiver->mainWindow->chatWindow.chatList.addChat(c);
        receiver->mainWindow->chatWindow.changeTo(c);
    });
    pack_start(startChat, Gtk::PACK_SHRINK);




    end:
    show_all_children();
}

ContactInfo::~ContactInfo() {
    hide();
}




