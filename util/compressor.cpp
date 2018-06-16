//
// Created by Trubeckoj Bogdan on 14.06.2018.
//

#include <iostream>
#include "compressor.h"

void compressor::compress(std::string w) {
    encoder Encoder(frequency);
    file_writer fw(w);
    for (size_t i = 0; i < 256; i++) {
        size_t sz = 8;
        char buffer[sz];
        size_t cur = frequency[i];
        for (int i = sz - 1; i >= 0; i--) {
            buffer[i] = static_cast<char>(cur % 256);
            cur /= 256;
        }
        fw.write(buffer, sz);
    }
    file_reader reader(file_name);
    std::vector<unsigned char> remain;
    while (!reader.eof()) {
        char buffer[reader.MAX_READ];
        size_t readed = reader.read(buffer, reader.MAX_READ);
        std::vector<unsigned char> buffer_cpy;
        for (size_t i = 0; i < readed; i++)
            buffer_cpy.push_back(static_cast<unsigned char>(buffer[i]));
        auto t = Encoder.encode(buffer_cpy);
        t.insert(t.begin(), remain.begin(), remain.end());
        remain.resize(0);
        size_t cnt = 0;
        for (size_t i = 0; i + 8 <= t.size(); i += 8) {
            unsigned char curChar = 0;
            for (size_t j = 0; j < 8; j++) {
                curChar *= 2;
                curChar += t[j + i];
            }
            buffer[cnt] = curChar;
            if (cnt == fw.MAX_WRITE - 1)
                fw.write(buffer, fw.MAX_WRITE);
            else {
                if (i + 8 + 8 > t.size()) {
                    fw.write(buffer, cnt + 1);
                }
            }
            cnt++;
            if (cnt == fw.MAX_WRITE)
                cnt = 0;
        }
        if ((t.size() % 8) != 0) {
            size_t pos = t.size() / 8 * 8;
            for (size_t i = pos; i < t.size(); i++) {
                remain.push_back(t[i]);
            }
        }
    }
    unsigned char curChar = 0;
    size_t cur = 7;
    for (unsigned char j : remain) {
        if (j) {
            curChar += (1 << cur);
        }
        cur--;
    }
    char buffer[1];
    buffer[0] = curChar;
    fw.write(buffer, 1);

    buffer[0] = static_cast<char>(8 - remain.size());
    fw.write(buffer, 1);

}

void compressor::get_frequency() {
    file_reader re(file_name);
    char buffer[re.MAX_READ];
    while (!re.eof()) {
        size_t readed = re.read(buffer, re.MAX_READ);
        for (size_t i = 0; i < readed; i++)
            frequency[static_cast<unsigned char>(buffer[i])]++;
    }
}
