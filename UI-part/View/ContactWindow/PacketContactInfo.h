//
// Created by ervinxie on 9/4/19.
//

#ifndef COURIER_CLIENT_PACKETCONTACTINFO_H
#define COURIER_CLIENT_PACKETCONTACTINFO_H

#include "GroupContactInfo.h"
class PacketContactInfo :public Gtk::VBox{
public:
    PacketContactInfo(PacketInfo*);
    PacketInfo*p;

    Gtk::Label label;
    Gtk::Button deleteBt;


};


#endif //COURIER_CLIENT_PACKETCONTACTINFO_H
