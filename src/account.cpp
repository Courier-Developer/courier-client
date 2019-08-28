//
// Created by 孙璋亮 on 2019-08-27.
//

#include "account.h"

/*
 *
 * @param username 用户名
 * @param password 密码
 * @param nickname 昵称
 * @return 注册状态 REGIST——SUCCESS,INVALID_USERNAME,INCORRECT_INFO,LINK_ERROR
 */
int regist(const std::string &username, const std::string &password, const std::string &nickname) {
    if (check_username_length(username) || check_password_length(password))
        return INCORRECT_INFO;
    // todo: call for the server's function

}

/*
 *
 * @param username 用户名
 * @return 长度状态 USERNAME_LENGTH,SUCCESS
 */
bool check_username_length(const std::string &username) {
    if (username.length() < 5 || username.length() > 20)
        return USERNAME_LENGTH_ERROR;
    else
        return SUCCESS;

}

/*
 *
 * @param password 用户名
 * @return 长度状态 USERNAME_LENGTH,SUCCESS
 */
bool check_password_length(const std::string &password) {
    if (password.length() < 6 || password.length() > 16)
        return PASSWORD_LENGTH_ERROR;
    else
        return SUCCESS;
}
