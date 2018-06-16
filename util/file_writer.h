//
// Created by Trubeckoj Bogdan on 09.06.2018.
//

#ifndef HAFFMUN_FILE_WRITER_H
#define HAFFMUN_FILE_WRITER_H

#include <fstream>

struct file_writer {
    //file_writer() = delete;
    explicit file_writer(std::string file_name);
    ~file_writer();
    void write(char* buffer, size_t buffer_size);
    const size_t MAX_WRITE = 1024;
    private:
        std::ofstream sstream;


};
#endif //HAFFMUN_FILE_WRITER_H
