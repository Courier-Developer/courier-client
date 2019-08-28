//
// Created by 孙璋亮 on 2019-08-28.
//

#ifndef COURIER_CLIENT_GROUP_INFO_H
#define COURIER_CLIENT_GROUP_INFO_H

#define NORMAL 0
#define SPECIAL_FOCUS 1
#define MUTE 2

#include <string>
#include <list>
#include "Member_Shortcut.h"

class Group_info {
private:
    unsigned int groupid;
    std::string avator_path;
    std::string groupname;
    int size;
    int online_user_number;
    std::list<Member_Shortcut> member;
public:
    unsigned int getGroupid() const;

    void setGroupid(unsigned int groupid);

    const std::string &getAvator_path() const;

    void setAvator_path(const std::string &avator_path);

    const std::string &getGroupname() const;

    void setGroupname(const std::string &groupname);

    int getSize() const;

    void setSize(int size);

    int getOnline_user_number() const;

    void setOnline_user_number(int online_user_number);

    const std::list<Member_Shortcut> &getMember() const;

    void setMember(const std::list<Member_Shortcut> &member);
};


#endif //COURIER_CLIENT_GROUP_INFO_H
