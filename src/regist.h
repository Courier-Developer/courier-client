//
// Created by 孙璋亮 on 2019-08-27.
//

#ifndef COURIER_CLIENT_REGIST_H
#define COURIER_CLIENT_REGIST_H

#include <string>
#define REGIST_SUCCESS 0
#define INVALID_USERNAME 1
#define USERNAME_LENGTH_ERROR 2
#define PSW_LENGTH_ERROR 3
#define LINK_ERROR 5

int regist(std::string username,std::string password);






#endif //COURIER_CLIENT_REGIST_H
