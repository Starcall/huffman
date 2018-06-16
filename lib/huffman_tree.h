//
// Created by Trubeckoj Bogdan on 06.06.2018.
//

#ifndef HAFFMUN_HUFFMAN_TREE_H
#define HAFFMUN_HUFFMAN_TREE_H

#include <cstdio>
#include <utility>
#include <vector>
#include <cstdint>



struct huffman_tree {
    huffman_tree() = default;

    explicit huffman_tree(std::vector<size_t>&); // create from frequency

    uint64_t get_code(unsigned char);

    size_t get_size(unsigned char);

    void move_left();
    void move_right();
    bool is_leaf();
    unsigned  char get_symbol();
    void reset();


    ~huffman_tree() {
        delete root;
        delete currentNode;
    };

private:

    std::vector<uint64_t> codes;
    std::vector<size_t> sz;

    struct node {
        node* left_child;
        node* right_child;
        unsigned char symbol;
        bool term;
        size_t count;
        node() {
            left_child = right_child = nullptr;
            symbol = 0;
            count = 0;
            term = false;
        }
        node (unsigned char symbol, size_t count, node* left_child, node* right_child, bool is_term) {
            this->left_child = left_child;
            this->right_child = right_child;
            this->symbol = symbol;
            this->count = count;
            this->term = is_term;
        }
        ~node () {
            if (this->left_child) delete left_child;
            if (this->right_child) delete right_child;
            this->left_child = nullptr;
            this->right_child = nullptr;
        }

    };

    node* root{};
    node* currentNode{};

    struct node_compare {
        bool operator () (const node* a, const node* b) {
            return a->count > b->count;
        }
    };

    void count_codes(node* , uint64_t, size_t);

};

#endif //HAFFMUN_HUFFMAN_TREE_H
