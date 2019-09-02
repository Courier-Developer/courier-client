//
// Created by ervinxie on 9/1/19.
//

#ifndef COURIER_CLIENT_GROUPCONTACTINFO_H
#define COURIER_CLIENT_GROUPCONTACTINFO_H

#include <gtkmm.h>
#include "ContactWindow.h"
#include "../../../Logic_Part/UI-Interface/GroupInfo.h"
class GroupContactInfo : public Gtk::VBox{
public:
    GroupContactInfo();
    GroupContactInfo(GroupInfo* group);
    virtual ~GroupContactInfo();
    GroupInfo* group;
protected:
    void ChangeGroup(GroupInfo* group);



};


#endif //COURIER_CLIENT_GROUPCONTACTINFO_H
