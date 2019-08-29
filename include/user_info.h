//
// Created by 孙璋亮 on 2019-08-29.
//

#ifndef COURIER_CLIENT_USER_INFO_H
#define COURIER_CLIENT_USER_INFO_H

#include <string>
#include "Date.h"

class user_info {
private:
    unsigned int id;
    std::string username;
    int status;   //在线状态
    std::string birthday;
    std::string nickname;
    std::string signature; //个性签名
    int isgroup;  //是否是群组；
    int groupid;  //!!!用户所处的分组id
    std::string avator_path; //头像路径
public:
    const bool check_nickname_length() const;
    const bool check_signature_length() const;
};


#endif //COURIER_CLIENT_USER_INFO_H
