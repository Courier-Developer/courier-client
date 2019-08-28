//
// Created by 孙璋亮 on 2019-08-28.
//

#ifndef COURIER_CLIENT_CHAT_SHORTCUT_H
#define COURIER_CLIENT_CHAT_SHORTCUT_H

#include <string>
#include "Date.h"
#define USERKIND 0
#define GROUPKIND 1

class Chat_Shortcut {
private:
    unsigned int id;
    int kind;
    std::string name;
    Date last_chat_time;    ///最后一次聊天的时间
    std::string last_chat_sentence;  ///聊天最后一句话的内容
public:
    unsigned int getId() const;

    void setId(unsigned int id);

    int getKind() const;

    void setKind(int kind);

    const std::string &getName() const;

    void setName(const std::string &name);

    const Date &getLast_chat_time() const;

    void setLast_chat_time(const Date &last_chat_time);

    const std::string &getLast_chat_sentence() const;

    void setLast_chat_sentence(const std::string &last_chat_sentence);
};


#endif //COURIER_CLIENT_CHAT_SHORTCUT_H
