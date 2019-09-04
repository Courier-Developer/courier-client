//
// Created by ervinxie on 9/2/19.
//

#include "View/implement.h"
#include "Receiver.h"


Receiver::Receiver(std::vector<PacketInfo *> &plist,
                   std::vector<GroupInfo *> &glist,
                   std::vector<ChatInfo *> &clist,
                   UserInfo *me) :
        plist(plist),
        glist(glist),
        clist(clist),
        me(me){}

void Receiver::debug() {
    std::cout << me->getNickName() << std::endl;
    for (auto p : plist) {
        std::cout << p->getName() << std::endl;
        for (auto u : *(p->getUsers())) {
            std::cout << u->getNickName() << std::endl;
        }
    }
    for (auto g : glist) {
        std::cout << g->getNickName() << std::endl;
        for (auto u : *(g->getUsers())) {
            std::cout << u->getNickName() << std::endl;
        }
    }
    for (auto c : clist) {
        std::cout << c->getTotype() << std::endl;
        if (c->getTotype() == 1) {
            std::cout << c->getToUser()->getNickName() << std::endl;
        } else {
            std::cout << c->getToGroup()->getNickName() << std::endl;
        }
        for (auto m : *(c->getMsgList())) {
            std::cout << m->getContent() << " " << m->getCreateTime().getString() << std::endl;
        }
    }

}

void Receiver::friendRequest(UserInfo * u) {
    Gtk::Dialog dialog;
    dialog.set_border_width(10);
    dialog.set_size_request(100,100);
    Glib::ustring info = "Someone wants to make friend with you!";
    Gtk::Label *label = Gtk::manage(new Gtk::Label(info));
    label->set_line_wrap(true);
    dialog.get_content_area()->pack_start(*label);
    dialog.get_action_area()->pack_start(*Gtk::manage(new ContactInfo(u,64,10)));
    dialog.add_button("Refuse", -1);
    dialog.add_button("Wait", 0);
    dialog.add_button("Accept", 1);
    dialog.show_all_children();
    int results=dialog.run();
    if (results==1) {
        dealer.agreefriend(u->getUserId(),[this](UserInfo*u){
            Gtk::Dialog dialog;
            dialog.set_border_width(10);
            dialog.set_size_request(100,100);
            Glib::ustring info = "Success!";
            Gtk::Label *label = Gtk::manage(new Gtk::Label(info));
            label->set_line_wrap(true);
            dialog.get_content_area()->pack_start(*label);
            dialog.get_action_area()->pack_start(*Gtk::manage(new ContactInfo(u,64,10)));
            dialog.add_button("OK", 1);
            this->friendUpdate(u);
            dialog.show_all_children();

            dialog.run();
            },[this](std::string err){
            Gtk::Dialog dialog;
            dialog.set_border_width(10);
            dialog.set_size_request(100,100);
            Glib::ustring info = err;
            Gtk::Label *label = Gtk::manage(new Gtk::Label(info));
            label->set_line_wrap(true);
            dialog.get_content_area()->pack_start(*label);
            dialog.add_button("OK", 1);
            dialog.show_all_children();
            dialog.run();
        });
    } else if(results==0){

    }else if(results==-1){

    }
}

void Receiver::receiveMessage(MessageInfo *msg) {
    mainWindow->chatWindow.receiveMsg(msg);
}

void Receiver::friendUpdate(UserInfo *u) {
    mainWindow->contactWindow.contactList.deleteFriend(u);
    mainWindow->contactWindow.contactList.addNewFriend(u);
}

void Receiver::friendDelete(UserInfo *u) {
    friendUpdate(u);
}

void Receiver::groupUpdate(GroupInfo *g) {
    mainWindow->contactWindow.contactList.deleteGroup(g);
    mainWindow->contactWindow.contactList.addNewGroup(g);
}

void Receiver::groupDelete(GroupInfo *g) {
    groupUpdate(g);
}

void Receiver::groupRequest(GroupInfo *g) {
    groupUpdate(g);
    mainWindow->chatWindow.chatList.addChat(g->getChat());
}




