//
// Created by Trubeckoj Bogdan on 09.06.2018.
//

#ifndef HAFFMUN_FILE_READER_H
#define HAFFMUN_FILE_READER_H

#include <fstream>

struct file_reader {
    file_reader() = default;;
    explicit file_reader(std::string file_name);
    ~file_reader();
    void open(std::string file_name);
    size_t read(char* buffer, size_t buffer_size);
    bool eof();
    const size_t MAX_READ = 2048;
    size_t rest();


private:
    std::ifstream sstream;
    size_t len{};
};

#endif //HAFFMUN_FILE_READER_H
