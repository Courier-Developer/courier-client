//
// Created by 孙璋亮 on 2019-08-28.
//

#include "Member_Shortcut.h"

void Member_Shortcut::setUser_id(unsigned int user_id) {
    Member_Shortcut::user_id = user_id;
}

void Member_Shortcut::setName(const std::string &name) {
    Member_Shortcut::name = name;
}

void Member_Shortcut::setAvator_path(const std::string &avator_path) {
    Member_Shortcut::avator_path = avator_path;
}

unsigned int Member_Shortcut::getUser_id() const {
    return user_id;
}

const std::string &Member_Shortcut::getName() const {
    return name;
}

const std::string &Member_Shortcut::getAvator_path() const {
    return avator_path;
}

int Member_Shortcut::getStatus() const {
    return status;
}

void Member_Shortcut::setStatus(int status) {
    Member_Shortcut::status = status;
}
