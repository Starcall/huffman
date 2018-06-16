//
// Created by Trubeckoj Bogdan on 09.06.2018.
//

#include <string>
#include "file_writer.h"

file_writer::file_writer(std::string file_name) {
    sstream.clear();
    sstream.open(file_name, std::ofstream::out | std::ofstream::binary);
}

file_writer::~file_writer() {
    sstream.close();
}

void file_writer::write(char *buffer, size_t buffer_size) {
    sstream.write(buffer, buffer_size);
}


