//
// Created by 孙璋亮 on 2019-08-28.
//

#include "File_handle.h"


/**
 *
 * @param path the path of file
 * @param mode openmode of file
 */

File_handle::File_handle(const std::string &path, std::ios_base::openmode mode) {
    try {
        fp.open(path, mode);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}


/**
 * clean the File_handle
 */
File_handle::~File_handle() {
    try {
        fp.close();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

}


