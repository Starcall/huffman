//
// Created by Trubeckoj Bogdan on 11.06.2018.
//

#ifndef HAFFMUN_DECODER_H
#define HAFFMUN_DECODER_H

#include "huffman_tree.h"

struct decoder {
    //decoder() = delete;
    explicit decoder(std::vector<size_t> frequency) : tree(frequency){
        tree.reset();
    };
    std::vector<unsigned char> decode(std::vector<unsigned char> &text, size_t);

private:
    huffman_tree tree;
};



#endif //HAFFMUN_DECODER_H
