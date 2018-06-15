//
// Created by Trubeckoj Bogdan on 14.06.2018.
//

#ifndef HAFFMUN_DECOMPRESSOR_H
#define HAFFMUN_DECOMPRESSOR_H

#include <cstddef>
#include <vector>
#include <string>

struct decompressor {
    decompressor(std::string file) {
        file_name = file;
        get_frequency();
    }
    void decompress(std::string to);
private:
    std::vector<size_t> frequency;
    std::string file_name;
    void get_frequency();
};


#endif //HAFFMUN_DECOMPRESSOR_H
