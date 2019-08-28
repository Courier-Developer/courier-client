//
// Created by 孙璋亮 on 2019-08-27.
//

#ifndef COURIER_CLIENT_ACCOUNT_H
#define COURIER_CLIENT_ACCOUNT_H

#include <string>

//Marco part
#define SUCCESS 0
#define REGIST_SUCCESS 0
#define INVALID_USERNAME 1
#define INCORRECT_INFO 2
#define USERNAME_LENGTH_ERROR 1
#define PASSWORD_LENGTH_ERROR 1
#define LINK_ERROR 5

int regist(const std::string &username, const std::string &password, const std::string &nickname);

bool check_username_length(const std::string &username);

bool check_password_length(const std::string &password);


#endif //COURIER_CLIENT_ACCOUNT_H
