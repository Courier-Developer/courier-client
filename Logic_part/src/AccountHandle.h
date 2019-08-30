//
// Created by 孙璋亮 on 2019-08-27.
//

#ifndef COURIER_CLIENT_ACCOUNT_H
#define COURIER_CLIENT_ACCOUNT_H

#include <string>
#include "LinkToServer.h"

//todo: there should be a full-scope my_profile

void signin(const link_to_server &link,const std::string &username, const std::string &password, const std::string &nickname);

const bool check_username_length(const std::string &username);

const bool check_password_length(const std::string &password);

const bool check_nickname_length(const std::string &nickname);

void login(link_to_server &link,std::string &username,std::string &password);

void update_profile(const link_to_server &link);



#endif //COURIER_CLIENT_ACCOUNT_H
