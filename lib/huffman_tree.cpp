//
// Created by Trubeckoj Bogdan on 06.06.2018.
//
#include <vector>
#include <queue>
#include <cassert>
#include <iostream>
#include "huffman_tree.h"

huffman_tree::huffman_tree(std::vector<size_t> &frequency) {
    codes.resize(256);
    sz.resize(256);
    std::priority_queue<node*, std::vector<node*>, node_compare> data;
    size_t counter = 0;
    for (size_t i = 0; i < frequency.size(); i++) {
        if (frequency[i] != 0) {
            data.emplace(new node(i, frequency[i], nullptr, nullptr, true));
            counter++;
        }
    }
    while (data.size() > 1) {
        node* first_node = data.top();
        data.pop();
        node* second_node = data.top();
        data.pop();
        data.emplace(new node(0, first_node->count + second_node->count, first_node, second_node, false));
    }
    if (counter == 0) return;
    this->root = data.top();
    if (counter == 1) {
        root->left_child = new node(data.top()->symbol, root->count, nullptr, nullptr, true);
        root->term = false;
        codes[this->root->left_child->symbol] = 0;
        sz[this->root->left_child->symbol] = 1;
    } else {
        count_codes(this->root, 0, 0);
    }

}

uint64_t huffman_tree::get_code(unsigned char symbol) {
    assert(sz[symbol] != 0);
    return codes[symbol];
}

void huffman_tree::count_codes(huffman_tree::node *cur_node, uint64_t cur_code, size_t depth) {
    if (cur_node == nullptr)
        return;
    count_codes(cur_node->left_child, cur_code << 1, depth + 1);
    if (cur_node->term) {
        codes[cur_node->symbol] = cur_code;
        sz[cur_node->symbol] = depth;
    }
    count_codes(cur_node->right_child, (cur_code << 1) + 1, depth + 1);
}

void huffman_tree::move_left() {
     if (is_leaf()) throw std::runtime_error("Decoded file is corrupted");
     currentNode = currentNode->left_child;

}

void huffman_tree::move_right() {
    if (is_leaf()) throw std::runtime_error("Decoded file is corrupted");
    currentNode = currentNode->right_child;

}

bool huffman_tree::is_leaf() {
    return currentNode->term;
}

void huffman_tree::reset() {
    currentNode = root;
}

unsigned char huffman_tree::get_symbol() {
    return currentNode->symbol;
}

size_t huffman_tree::get_size(unsigned char symbol) {
    return sz[symbol];
}




