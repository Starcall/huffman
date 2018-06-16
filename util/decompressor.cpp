//
// Created by Trubeckoj Bogdan on 14.06.2018.
//

#include <iostream>
#include "decompressor.h"
#include "file_reader.h"
#include "../lib/decoder.h"
#include "file_writer.h"

void decompressor::get_frequency() {
    frequency.resize(256);
    file_reader fr(file_name);
    char buffer[fr.MAX_READ];
    fr.read(buffer, fr.MAX_READ);
    for (size_t i = 0; i < fr.MAX_READ / 8; i++) {
        size_t cur = 0;
        for (size_t j = 0; j < 8; j++) {
            cur *= 256;
            size_t x = static_cast<unsigned char>(buffer[i * 8 + j]);
            cur += x;
        }
        frequency[i] = cur;
    }
    fr.read(buffer, fr.MAX_READ);
    for (size_t i = 0; i < fr.MAX_READ / 8; i++) {
        size_t cur = 0;
        for (size_t j = 0; j < 8; j++) {
            cur *= 256;
            size_t x = static_cast<unsigned char>(buffer[i * 8 + j]);
            cur += x;
        }
        frequency[i + fr.MAX_READ / 8] = cur;
    }

}

void decompressor::decompress(std::string to) {
    decoder d(frequency);
    file_reader fr(file_name);
    file_writer fw(to);
    char buffer[fr.MAX_READ];
    size_t foo = fr.read(buffer, fr.MAX_READ);
    foo = fr.read(buffer, fr.MAX_READ);
    std::vector<unsigned char> remain;
    while (!fr.eof()) {
        size_t readed = fr.read(buffer, fr.MAX_READ);
        size_t fool = 0;
        if (fr.eof()) {
            fool = static_cast<size_t>(8 + static_cast<unsigned char>(buffer[readed - 1]));
        }
        std::vector<unsigned char> buffer_cpy;
        for (size_t i = 0; i < readed; i++)
            buffer_cpy.push_back(static_cast<unsigned char>(buffer[i]));
        auto decoded = d.decode(buffer_cpy, fool);

        //for (auto i : decoded) std::cout << (char)i;
        size_t cnt = 0;
        for (size_t i = 0; i < decoded.size(); i++) {
            buffer[cnt] = decoded[i];
            cnt++;
            if (cnt == fw.MAX_WRITE) {
                cnt = 0;
                fw.write(buffer, fw.MAX_WRITE);
            } else {
                if (i + 1 == decoded.size()) {
                    fw.write(buffer, cnt);
                }
            }
        }
    }

}
