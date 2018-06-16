#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <vector>
#include <utility>
#include "../gtest/gtest.h"
#include <ctime>
#include <string>
#include <iostream>

#include "util/compressor.h"
#include "util/decompressor.h"

#include "../lib/decoder.h"
#include "../lib/encoder.h"



TEST(correctness, one_string_test) {
    std::string file = "my_test";
    std::ofstream out(file + ".in");
    std::string test = "some testaklmROQV3RN 0J9123";
    out << test;
    out.close();
    compressor fe(file + ".in");
    fe.compress(file + ".huf");
    decompressor fd(file + ".huf");
    fd.decompress(file + ".out");

    std::ifstream in(file + ".out");
    std::string res;
    getline(in, res);
    in.close();

    EXPECT_EQ(res, test);
}

TEST(correctness, empty) {
    std::string file = "my_test";
    std::ofstream out(file + ".in");
    std::string test = "";
    out.close();
    compressor fe(file + ".in");
    fe.compress(file + ".huf");
    decompressor fd(file + ".huf");
    fd.decompress(file + ".out");

    std::ifstream in(file + ".out");
    std::string res;
    getline(in, res);
    in.close();

    EXPECT_EQ(res, test);
}

TEST(correctness, random_without_new_lines) {
    for (size_t w = 0; w < 1000; w++) {
        std::string file = "my_test";
        std::ofstream out(file + ".in");
        std::string test = "";
        for (size_t i = 0; i < rand() % 100000000; i++) {
            char c = rand() % 255;
            if (c == '\n') continue;
            test += c;
        }
        out << test;
        out.close();
        compressor fe(file + ".in");
        fe.compress(file + ".huf");
        decompressor fd(file + ".huf");
        fd.decompress(file + ".out");

        std::ifstream in(file + ".out");
        std::string res;
        getline(in, res);
        in.close();

        EXPECT_EQ(res, test);
    }
}