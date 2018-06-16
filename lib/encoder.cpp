//
// Created by Trubeckoj Bogdan on 09.06.2018.
//

#include <vector>
#include "encoder.h"

std::vector<bool> encoder::encode(char* text, size_t text_size) {
    std::vector<bool> ans;
    for (size_t i = 0; i < text_size; i++) {
        unsigned char c = static_cast<unsigned char> (text[i]);
        uint64_t curCode = tree.get_code(c);
        for (size_t j = 0; j < tree.get_size(c); j++) {
            auto curBit = static_cast<bool>(curCode & 1);
            ans.push_back(curBit);
            curCode >>= 1;
        }
        std::reverse(ans.rbegin(), ans.rbegin() + tree.get_size(c));
    }
    return ans;
}
