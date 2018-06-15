//
// Created by Trubeckoj Bogdan on 14.06.2018.
//

#ifndef HAFFMUN_COMPRESSOR_H
#define HAFFMUN_COMPRESSOR_H
#include <string>
#include "file_reader.h"
#include "file_writer.h"
#include "../lib/encoder.h"

struct compressor {
    explicit compressor(std::string input_file) {
        file_name = input_file;
        frequency.resize(256);
        get_frequency();
    }

    void compress(std::string w);

private:
    std::vector<size_t> frequency;
    std::string file_name;
    void get_frequency();
};
#endif //HAFFMUN_COMPRESSOR_H
