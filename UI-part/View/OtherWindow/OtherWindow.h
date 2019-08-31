//
// Created by ervinxie on 8/29/19.
//

#ifndef GTKMM_OTHERWINDOW_H
#define GTKMM_OTHERWINDOW_H

#include <gtkmm.h>
#include "../ContactWindow/ContactInfo.h"

class OtherWindow :public Gtk::HBox{
public:
    OtherWindow();
    virtual ~OtherWindow();

protected:
    ContactInfo* myInfo;


};


#endif //GTKMM_OTHERWINDOW_H
