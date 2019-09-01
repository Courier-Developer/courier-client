//
// Created by 孙璋亮 on 2019-08-30.
//

#ifndef COURIER_CLIENT_LOGIC_PART_H
#define COURIER_CLIENT_LOGIC_PART_H


#include "UI_Part.h"
class UI_Part;
class Logic_Part {
private:
    UI_Part &UI;
    LinkToSever &Link;
public:
    void bind(const UI_Part &ui){
        UI=ui;
    }

};


#endif //COURIER_CLIENT_LOGIC_PART_H
