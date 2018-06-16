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

TEST(correctness, one_symbol) {
    std::string file = "my_test";
    std::ofstream out(file + ".in");
    std::string test = "q";
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

TEST(correctness, all_symbols) {
    std::string file = "my_test";
    std::ofstream out(file + ".in");
    std::string test = "";
    for (int i = 0; i != 256; i++) {
        if ((char)i != '\n')
            test += (unsigned char) i;
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

TEST(correctness, random) {
    srand(time(0));
    for (size_t w = 0; w < 10; w++) {
        std::string file = "my_test";
        std::ofstream out(file + ".in");
        std::string test = "";
        size_t cnt = rand() % 1000000;
        for (size_t i = 0; i < cnt; i++) {
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


TEST(correctness, mb_200_test) {
        std::string test = "";
        std::ifstream o("new_file");
        char c;
        while (o >> c) test += c;
        o.close();
        compressor fe("new_file");
        fe.compress("new_file.huf");
        decompressor fd("new_file.huf");
        fd.decompress("new_file.out");

        std::ifstream in("new_file.out");
        std::string res;

        while (in >> c) res += c;
        in.close();

        EXPECT_EQ(res, test);
}