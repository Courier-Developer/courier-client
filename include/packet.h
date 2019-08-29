//
// Created by 孙璋亮 on 2019-08-29.
//

#ifndef COURIER_CLIENT_PACKET_H
#define COURIER_CLIENT_PACKET_H

#include <string>
#include <vector>
#include "user_info.h"


class packet {
    int packetid;
    std::string packetname;
    std::vector<user_info> group;

};




#endif //COURIER_CLIENT_PACKET_H
