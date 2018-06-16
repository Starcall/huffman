//
// Created by Trubeckoj Bogdan on 09.06.2018.
//

#include <vector>
#include "encoder.h"

std::vector<unsigned char> encoder::encode(char* text, size_t text_size) noexcept {
    std::vector<unsigned char> ans;
    for (size_t i = 0; i < text_size; i++) {
        auto c = static_cast<unsigned char> (text[i]);
        uint64_t curCode = tree.get_code(c);
        size_t curSize = tree.get_size(c);
        for (size_t j = 0; j < curSize; j++) {
            auto curBit = static_cast<unsigned char>(curCode & 1);
            ans.push_back(curBit);
            curCode >>= 1;
        }
        std::reverse(ans.rbegin(), ans.rbegin() + curSize);
    }
    return ans;
}
