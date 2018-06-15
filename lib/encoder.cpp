//
// Created by Trubeckoj Bogdan on 09.06.2018.
//

#include <vector>
#include "encoder.h"

std::vector<unsigned char> encoder::encode(std::vector<unsigned char> &text) {
    std::vector<unsigned char> ans;
    for (unsigned char &c : text) {
        uint64_t curCode = tree.get_code(c);
        for (size_t i = 0; i < tree.get_size(c); i++) {
            auto curBit = static_cast<unsigned char>(curCode % 2);
            ans.push_back(curBit);
            curCode /= 2;
        }
        std::reverse(ans.rbegin(), ans.rbegin() + tree.get_size(c));
    }
    return ans;
}
