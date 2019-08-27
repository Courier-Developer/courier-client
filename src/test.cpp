//
// Created by 孙璋亮 on 2019-08-27.
//

#include "pthread.h"
#include <iostream>
#include <zconf.h>

void* say(void* arg)
{
    std::cout<<"hello"<<std::endl;
}

pthread_t pid;
int main()
{
    for (int i=0;i<4;i++)
    {
        pthread_create(&pid,NULL,say,NULL);
    }
    sleep(20);
    return 0;
}