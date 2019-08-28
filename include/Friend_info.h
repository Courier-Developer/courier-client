//
// Created by 孙璋亮 on 2019-08-28.
//

#ifndef COURIER_CLIENT_FRIENDINFO_H
#define COURIER_CLIENT_FRIENDINFO_H

#include <string>

class Friend_info {
private:
    std::string avator_path;
    unsigned int id;
    std::string username;
    std::string nickname;
public:
    const std::string &getAvator_path() const;

    void setAvator_path(const std::string &avator_path);

    unsigned int getId() const;

    void setId(unsigned int id);

    const std::string &getUsername() const;

    void setUsername(const std::string &username);

    const std::string &getNickname() const;

    void setNickname(const std::string &nickname);

public:

};


#endif //COURIER_CLIENT_FRIENDINFO_H
