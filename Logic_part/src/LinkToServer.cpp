//
// Created by 孙璋亮 on 2019-08-29.
//

#include "LinkToServer.h"


const unsigned int link_to_server::login(const std::string &username,const std::string &password) {
    //todo:
    // std::pair<unsigned int,std::string> code = rpc.call<std::pair<unsigned int,std::string> >("user_login",username,password);
    auth_code=code.second;
    auth_id=code.first;
    return auth_id;
}

bool link_to_server::signin(const std::string &username,const std::string &password, const std::string &nickname) const{
    //todo:
    // bool finished=rpc.call<bool>("user_signin",username,password,nickname);
    return finished;
}

bool link_to_server::updateprofile(const user_info &profile) const {
    //todo:
    // bool finished=rpc.call<bool>("user_profile_update",profile);
    return finished;
}



