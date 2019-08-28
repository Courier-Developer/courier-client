//
// Created by 孙璋亮 on 2019-08-28.
//

#include "Chat_Shortcut.h"

unsigned int Chat_Shortcut::getId() const {
    return id;
}

void Chat_Shortcut::setId(unsigned int id) {
    Chat_Shortcut::id = id;
}

int Chat_Shortcut::getKind() const {
    return kind;
}

void Chat_Shortcut::setKind(int kind) {
    Chat_Shortcut::kind = kind;
}

const std::string &Chat_Shortcut::getName() const {
    return name;
}

void Chat_Shortcut::setName(const std::string &name) {
    Chat_Shortcut::name = name;
}

const Date &Chat_Shortcut::getLast_chat_time() const {
    return last_chat_time;
}

void Chat_Shortcut::setLast_chat_time(const Date &last_chat_time) {
    Chat_Shortcut::last_chat_time = last_chat_time;
}

const std::string &Chat_Shortcut::getLast_chat_sentence() const {
    return last_chat_sentence;
}

void Chat_Shortcut::setLast_chat_sentence(const std::string &last_chat_sentence) {
    Chat_Shortcut::last_chat_sentence = last_chat_sentence;
}
