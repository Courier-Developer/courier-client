//
// Created by 孙璋亮 on 2019-08-29.
//

#include "user_info.h"
#include "../src/MacroDefinition.h"

const bool user_info::check_nickname_length() const {
    if (nickname.length()<1 || nickname.length()>20)
        return LENGTH_ERROR;
    else
        return SUCCESS;
}

const bool user_info::check_signature_length() const {
    if (nickname.length()>300)
        return LENGTH_ERROR;
    else
        return SUCCESS;
}
