//
// Created by 孙璋亮 on 2019-08-29.
//

#ifndef COURIER_CLIENT_USER_INFO_H
#define COURIER_CLIENT_USER_INFO_H

#include <string>
#include <vector>
#include "Message.h"


class User {
public:
    virtual unsigned int getUserId() = 0;

    virtual std::string getUserName() = 0;

    virtual std::string getNickName() = 0;

    virtual std::string getAvatarPath() = 0;

    virtual std::string getSignature() = 0;




};


#endif //COURIER_CLIENT_USER_INFO_H