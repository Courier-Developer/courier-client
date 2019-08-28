//
// Created by 孙璋亮 on 2019-08-28.
//

#ifndef COURIER_CLIENT_FILE_HANDLE_H
#define COURIER_CLIENT_FILE_HANDLE_H

#include <fstream>
#include <iostream>
#include <stdexcept>

class File_handle {
private:
    std::fstream fp;
public:
    File_handle(const std::string &, std::ios_base::openmode);

    ~File_handle();
};


#endif //COURIER_CLIENT_FILE_HANDLE_H
