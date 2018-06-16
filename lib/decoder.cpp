//
// Created by Trubeckoj Bogdan on 14.06.2018.
//

#include <vector>
#include <iostream>
#include "decoder.h"

std::vector<unsigned char> decoder::decode(std::vector<unsigned char> &text, size_t fool) {
    std::vector<unsigned char> ans;
    std::vector<bool> realText;
    for (unsigned char i : text) {
        for (int j = 7; j >= 0; j--) {
            if ((i & (1 << j)) != 0) {
                realText.push_back(1);
            } else {
                realText.push_back(0);
            }
        }
    }
    if (realText.size() < fool) {
        throw std::runtime_error("My code does not work, sorry");
    }
    //for (size_t i = 0; i < fool; i++) realText.pop_back();
    realText.erase(realText.begin() + realText.size() - fool, realText.end());
    for (bool i : realText) {
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
    if (!realText.empty() && tree.is_leaf()) {
        ans.push_back(tree.get_symbol());
        tree.reset();
    }
    return ans;
}
