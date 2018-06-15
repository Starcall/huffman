//
// Created by Trubeckoj Bogdan on 14.06.2018.
//

#include <vector>
#include "decoder.h"

std::vector<unsigned char> decoder::decode(std::vector<unsigned char> &text, size_t fool) {
    std::vector<unsigned char> ans;
    std::vector<unsigned char> realText;
    for (unsigned char i : text) {
        for (int j = 7; j >= 0; j--) {
            if ((i & (1 << j)) != 0) {
                realText.push_back(1);
            } else {
                realText.push_back(0);
            }
        }
    }
    realText.erase(realText.begin() + realText.size() - fool, realText.end());
    for (unsigned char i : realText) {
        if (tree.is_leaf()) {
            ans.push_back(tree.get_symbol());
            tree.reset();
        }
        if (i == 1) {
            tree.move_right();
        } else {
            tree.move_left();
        }
    }
    if (tree.is_leaf()) {
        ans.push_back(tree.get_symbol());
        tree.reset();
    }
    return ans;
}
