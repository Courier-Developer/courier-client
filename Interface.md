# client 逻辑部分

**TIPS：在这个部分中，出现错误返回值通常>0,成功通常返回**

| Macro                 | 实际值 | 描述                              |
| --------------------- | ------ | --------------------------------- |
| SUCCESS               | 0      | 成功                              |
| REGIST_SUCCESS        | 0      | 注册成功                          |
| INVALID_USERNAME      | 1      | 用户名已被注册                    |
| USERNAME_LENGTH_ERROR | 1      | 用户名少于5个字节或多于20个字节   |
| PASSWORD_LENGTH_ERROR | 1      | 密码少于6个字节或密码多于16个字节 |
| INCORRECT_INFO        | 2      | 信息填写不符合规范                |
| LINK_ERROR            | -1     | 与服务端的连接出现问题            |

# account.h

主要是负责登陆界面的信息维护

### 注册部分

#### check_username_length 检查用户名长度

```c++
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
```

#### check_password_length 检查密码长度

```c++
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
```

#### regist 提交注册

```c++
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
```



