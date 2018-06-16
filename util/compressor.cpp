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
            cur >>= 8;// 256;
        }
        cnt += 8;
        if (cnt == fw.MAX_WRITE) {
            fw.write(buffer, fw.MAX_WRITE);
            cnt = 0;
        }

    }
    file_reader reader(file_name);
    std::vector<bool> remain;
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
        if ((t.size() & 7) != 0) {
            size_t pos = t.size() / 8 * 8;
            for (size_t i = pos; i < t.size(); i++) {
                remain.push_back(t[i]);
            }
        }
    }
    unsigned char curChar = 0;
    size_t cur = 7;
    for (bool j : remain) {
        if (j) {
            curChar += (1 << cur);
        }
        cur--;
    }
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
