//
// Created by 孙璋亮 on 2019-08-28.
//
#include <iostream>
#include <zconf.h>
#include <map>
#include <User.h>
#include "LinkToServer.h"

std::map<unsigned int,User*> IdToUser;


void init()
{
    IdToUser.clear();
}

int main()
{
    MessageInfo fuck;
    printf("%s..\n",fuck.getContent());
}