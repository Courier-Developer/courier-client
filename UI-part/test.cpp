//
// Created by ervinxie on 8/30/19.
//
#include <iostream>
#include "Interface/DateTime.h"
int main(int argc, char *argv[])
{
    DateTime d(1998, 1, 1, 23, 45, 12);
    std::cout <<d.getString() << std::endl;
    for(int i=0;i<6;i++){
        std::cout<<d.t[i]<<std::endl;
    }

    return 0;
}