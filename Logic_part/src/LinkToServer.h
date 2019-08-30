//
// Created by 孙璋亮 on 2019-08-29.
//

#ifndef COURIER_CLIENT_LINK_TO_SERVER_H
#define COURIER_CLIENT_LINK_TO_SERVER_H

#include <string>
#include <thread>
#include <mutex>
#include <iostream>

/**
 * 负责和服务器的交互部分
 */
class link_to_server {
private:
    std::mutex lock;
    std::string auth_code;
    unsigned int auth_id;

public:
    static void heartbeat();
    static void init();
//    const unsigned int login(const std::string &username,const std::string &password);
//    bool signin(const std::string &username,const std::string &password,const std::string &nickname) const;
//    bool updateprofile(const user_info &profile) const;
};


#endif //COURIER_CLIENT_LINK_TO_SERVER_H
