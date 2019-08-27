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
int regist(std::string username,std::string password,std::string nickname)
{
    if (check_username_length(username) || check_password_length(password))
        return INCORRECT_INFO;
    // todo: call for the server's function

}

/*
 *
 * @param username 用户名
 * @return 长度状态 USERNAME_LENGTH,SUCCESS
 */
bool check_username_length(std::string username)
{
    if (username.len()<5||username,len()>20)
        return USERNAME_LENGTH_ERROR;
    else
        return SUCCESS;
}

/*
 *
 * @param password 用户名
 * @return 长度状态 USERNAME_LENGTH,SUCCESS
 */
bool check_password_length(std::string password)
{
    if (password.len()<6 || password.len()>16)
        return PASSWORD_LENGTH_ERROR;
    else
        return SUCCESS;
}
