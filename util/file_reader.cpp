//
// Created by Trubeckoj Bogdan on 09.06.2018.
//

#include <string>
#include <iostream>
#include "file_reader.h"
file_reader::file_reader(std::string file_name) {

    open(file_name);
}

file_reader::~file_reader() {
    sstream.close();
}

void file_reader:: open(std::string file_name) {
    sstream.clear();
    sstream.open(file_name, std::ifstream::in | std::ifstream::binary);
    if (!sstream.is_open()) {
        sstream.close();
        throw std::runtime_error("No such file founчd");
    }
    sstream.seekg (0, sstream.end);
    len = static_cast<size_t>(sstream.tellg());
    sstream.seekg (0, sstream.beg);

}

bool file_reader::eof() {
    return (len == 0);
}

size_t file_reader::rest() {
    return len;
}

size_t file_reader::read(char *buffer, size_t buffer_size) {

    buffer_size = std::min(buffer_size, len);
    sstream.read(buffer, buffer_size);
    len -= buffer_size;
    return buffer_size;
}

