//
// Created by Trubeckoj Bogdan on 14.06.2018.
//

#include <vector>
#include <iostream>
#include "decoder.h"

std::vector<unsigned char> decoder::decode(std::vector<unsigned char> &realText) {
    std::vector<unsigned char> ans;
 
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
    if (!realText.empty() && tree.is_leaf()) {
        ans.push_back(tree.get_symbol());
        tree.reset();
    }
    return ans;
}
