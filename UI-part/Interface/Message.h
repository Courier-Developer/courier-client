//
// Created by 孙璋亮 on 2019-08-29.
//

#ifndef COURIER_CLIENT_MESSAGE_INFO_H
#define COURIER_CLIENT_MESSAGE_INFO_H

#include <string>
//排完序返回
#include "User.h"
#include "DateTime.h"

class Message {
private:
    virtual User *getSender;
    virtual Chat *getChat;

    virtual int getType() = 0;

    virtual DateTime getCreateTime() = 0;

    virtual std::string getContent() = 0;

    virtual int getStatus() = 0;

};


#endif //COURIER_CLIENT_MESSAGE_INFO_H
