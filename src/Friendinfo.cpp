//
// Created by 孙璋亮 on 2019-08-28.
//

#include "Friendinfo.h"

const std::string &Friendinfo::getAvator_path() const {
    return avator_path;
}

void Friendinfo::setAvator_path(const std::string &avator_path) {
    Friendinfo::avator_path = avator_path;
}

unsigned int Friendinfo::getId() const {
    return id;
}

void Friendinfo::setId(unsigned int id) {
    Friendinfo::id = id;
}

const std::string &Friendinfo::getUsername() const {
    return username;
}

void Friendinfo::setUsername(const std::string &username) {
    Friendinfo::username = username;
}

const std::string &Friendinfo::getNickname() const {
    return nickname;
}

void Friendinfo::setNickname(const std::string &nickname) {
    Friendinfo::nickname = nickname;
}
