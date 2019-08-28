//
// Created by 孙璋亮 on 2019-08-28.
//

//群内成员信息剪影，只显示部分信息
#ifndef COURIER_CLIENT_SHORTCUT_H
#define COURIER_CLIENT_SHORTCUT_H


#include <string>

class Shortcut {
    unsigned int user_id;
    std::string name;
    std::string avator_path;
public:
    const std::string &getName() const;

    const std::string &getAvator_path() const;

    unsigned int getUser_id() const;

    void setUser_id(unsigned int user_id);

    void setName(const std::string &name);

    void setAvator_path(const std::string &avator_path);
};


#endif //COURIER_CLIENT_SHORTCUT_H
