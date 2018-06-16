//
// Created by Trubeckoj Bogdan on 14.06.2018.
//

#include <iostream>
#include "compressor.h"

void compressor::compress(std::string w) {
    encoder Encoder(frequency);
    file_writer fw(w);
    size_t cnt = 0;
    char buffer[fw.MAX_WRITE];
    for (size_t i = 0; i < 256; i++) {
        size_t cur = frequency[i];
        for (int j = 7; j >= 0; j--) {
            buffer[cnt + j] = static_cast<char>(cur & 255);
            cur >>= 8;
        }
        cnt += 8;
        if (cnt == fw.MAX_WRITE) {
            fw.write(buffer, fw.MAX_WRITE);
            cnt = 0;
        }

    }
    file_reader reader(file_name);
    std::vector<unsigned char> remain;
    while (!reader.eof()) {
        char new_buffer[reader.MAX_READ];
        size_t readed = reader.read(new_buffer, reader.MAX_READ);
        auto t = Encoder.encode(new_buffer, readed);
        t.insert(t.begin(), remain.begin(), remain.end());
        remain.resize(0);
        cnt = 0;
        for (size_t i = 0; i + 8 <= t.size(); i += 8) {
            unsigned char curChar = 0;
            for (size_t j = 0; j < 8; j++) {
                curChar <<= 1;
                curChar |= t[j + i];
            }
            buffer[cnt] = curChar;
            cnt++;
            if (cnt == fw.MAX_WRITE) {
                fw.write(buffer, fw.MAX_WRITE);
                cnt = 0;
            }
        }
        if (cnt) {
            fw.write(buffer, cnt);
        }
        if ((t.size() & 7) != 0) {
            size_t pos = t.size() / 8 * 8;
            remain.resize(t.size() - pos);
            std::copy(t.begin() + pos, t.end(), remain.begin());
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
    buffer[0] = curChar;
    buffer[1] = static_cast<char>(8 - remain.size());
    fw.write(buffer, 2);
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
