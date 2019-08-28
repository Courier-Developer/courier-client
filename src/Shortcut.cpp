//
// Created by 孙璋亮 on 2019-08-28.
//

#include "Shortcut.h"

void Shortcut::setUser_id(unsigned int user_id) {
    Shortcut::user_id = user_id;
}

void Shortcut::setName(const std::string &name) {
    Shortcut::name = name;
}

void Shortcut::setAvator_path(const std::string &avator_path) {
    Shortcut::avator_path = avator_path;
}

unsigned int Shortcut::getUser_id() const {
    return user_id;
}

const std::string &Shortcut::getName() const {
    return name;
}

const std::string &Shortcut::getAvator_path() const {
    return avator_path;
}
