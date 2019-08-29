//
// Created by 孙璋亮 on 2019-08-29.
//

#ifndef COURIER_CLIENT_MESSAGE_INFO_H
#define COURIER_CLIENT_MESSAGE_INFO_H

#include <string>
//排完序返回

class message_info {
private:
    unsigned int id; //发送失败本地数据库存储为NULL
    std::string sender_nickname;   //发送人的昵称
    unsigned int from; //发送该消息人的id;
    unsigned int to; //接收该消息人的id；
    int type;    //类型，文本/文件/图片
    std::string create_time;
    std::string edit_time;
    std::string content; //文件图片为路径
    int IstoGroup; //是否是群消息
    int status; //消息是否成功由本地发送至服务器
};


#endif //COURIER_CLIENT_MESSAGE_INFO_H
