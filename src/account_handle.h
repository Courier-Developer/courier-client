//
// Created by 孙璋亮 on 2019-08-27.
//

#ifndef COURIER_CLIENT_ACCOUNT_H
#define COURIER_CLIENT_ACCOUNT_H

#include <string>
#include <user_info.h>
#include "link_to_server.h"

extern user_info my_profile;

void signin(const link_to_server &link,const std::string &username, const std::string &password, const std::string &nickname);

const bool check_username_length(const std::string &username);

const bool check_password_length(const std::string &password);

const bool check_nickname_length(const std::string &nickname);





#endif //COURIER_CLIENT_ACCOUNT_H
