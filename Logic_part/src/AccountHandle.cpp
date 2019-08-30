//
// Created by 孙璋亮 on 2019-08-27.
//

#include "AccountHandle.h"
#include "MacroDefinition.h"
#include "LinkToServer.h"

/**
 *
 * @param link
 * @param username
 * @param password
 * @param nickname
 */
void signin(const link_to_server &link,const std::string &username, const std::string &password, const std::string &nickname) {
    if (check_username_length(username) || check_password_length(password) || check_nickname_length(nickname)){
        //todo: call for UI
        return;
    }
    if (link.signin(username,password,nickname))
    {
        //todo: call for UI
    }
    // todo: call for the server's function

}

/**
 *
 * @param username
 * @return
 */
const bool check_username_length(const std::string &username) {
    if (username.length() < 5 || username.length() > 20)
        return LENGTH_ERROR;
    else
        return SUCCESS;
}

/**
 *
 * @param password
 * @return
 */
const bool check_password_length(const std::string &password) {
    if (password.length() < 6 || password.length() > 16)
        return LENGTH_ERROR;
    else
        return SUCCESS;
}

/**
 *
 * @param nickname
 * @return
 */
const bool check_nickname_length(const std::string &nickname) {
    if (nickname.length() < 1 || nickname.length() > 20)
        return LENGTH_ERROR;
    else
        return SUCCESS;
}

/**
 *
 */
void logout() {
    // todo: call for the server to logout
}


/**
 *
 * @param link
 * @param username
 * @param password
 */
void login(link_to_server &link,std::string &username,std::string &password) {
    if (check_username_length(username)|| check_password_length(password)) {
    // todo: call for the UI
        return;
    }
    unsigned int myid = link.login(username, password);
//    if (myid>0)
    //todo: link the local database
    // todo:call for the UI
}

/**
 *
 * @param link
 */
void update_profile(const link_to_server &link)
{
    if (my_profile.check_nickname_length()){
        //todo: call for UI
        return;
    }
    if (my_profile.check_signature_length())
    {
        //todo: call for UI
        return;
    }
    if (link.updateprofile(my_profile))
    {
        //todo:  call for the UI
        return;
    }
}