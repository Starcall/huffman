//
// Created by Trubeckoj Bogdan on 06.06.2018.
//

#ifndef HAFFMUN_ENCODER_H
#define HAFFMUN_ENCODER_H

#include <utility>

#include "huffman_tree.h"

struct encoder {
    //encoder() = delete;
    explicit encoder(std::vector<size_t> &data) : tree(data) {};
    std::vector<unsigned char> encode(char*, size_t ) noexcept ;

private:
    huffman_tree tree;
};

#endif //HAFFMUN_ENCODER_H
