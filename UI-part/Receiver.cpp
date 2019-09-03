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

void Receiver::friendRequest(UserInfo *) {
    Gtk::Dialog dialog;
    dialog.set_border_width(10);
    dialog.set_size_request(100,100);
    Glib::ustring info = "Someone wants to make friend with you!";
    Gtk::Label *label = Gtk::manage(new Gtk::Label(info));
    label->set_line_wrap(true);
    dialog.get_content_area()->pack_start(*label);
    dialog.add_button("Refuse", -1);
    dialog.add_button("Wait", 0);
    dialog.add_button("Accept", 1);
    dialog.show_all_children();
    int results=dialog.run();
    if (results==1) {

    } else if(results==0){

    }else if(results==-1){

    }
}
