//
// Created by 孙璋亮 on 2019-08-28.
//

#include "Friend_info.h"

const std::string &Friend_info::getAvator_path() const {
    return avator_path;
}

void Friend_info::setAvator_path(const std::string &avator_path) {
    Friend_info::avator_path = avator_path;
}

unsigned int Friend_info::getId() const {
    return id;
}

void Friend_info::setId(unsigned int id) {
    Friend_info::id = id;
}

const std::string &Friend_info::getUsername() const {
    return username;
}

void Friend_info::setUsername(const std::string &username) {
    Friend_info::username = username;
}

const std::string &Friend_info::getNickname() const {
    return nickname;
}

void Friend_info::setNickname(const std::string &nickname) {
    Friend_info::nickname = nickname;
}
