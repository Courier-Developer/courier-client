//
// Created by 孙璋亮 on 2019-08-28.
//

#include "Group_info.h"

unsigned int Group_info::getGroupid() const {
    return groupid;
}

void Group_info::setGroupid(unsigned int groupid) {
    Group_info::groupid = groupid;
}

const std::string &Group_info::getAvator_path() const {
    return avator_path;
}

void Group_info::setAvator_path(const std::string &avator_path) {
    Group_info::avator_path = avator_path;
}

const std::string &Group_info::getGroupname() const {
    return groupname;
}

void Group_info::setGroupname(const std::string &groupname) {
    Group_info::groupname = groupname;
}

int Group_info::getSize() const {
    return size;
}

void Group_info::setSize(int size) {
    Group_info::size = size;
}

int Group_info::getOnline_user_number() const {
    return online_user_number;
}

void Group_info::setOnline_user_number(int online_user_number) {
    Group_info::online_user_number = online_user_number;
}

const std::list<Shortcut> &Group_info::getMember() const {
    return member;
}

void Group_info::setMember(const std::list<Shortcut> &member) {
    Group_info::member = member;
}
