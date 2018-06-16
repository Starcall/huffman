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
    char buffer[2048];
    fr.read(buffer, 2048);
    for (size_t i = 0; i < 2048 / 8; i++) {
        size_t cur = 0;
        for (size_t j = 0; j < 8; j++) {
            cur <<= 8;
            cur += static_cast<unsigned char>(buffer[i * 8 + j]);
        }
        frequency[i] = cur;
    }
}

void decompressor::decompress(std::string to) {
    decoder d(frequency);
    file_reader fr(file_name);
    file_writer fw(to);
    char buffer[fr.MAX_READ];
    fr.read(buffer, 2048);
    std::vector<unsigned char> remain;
    while (!fr.eof()) {
        size_t readed = fr.read(buffer, fr.MAX_READ);
        size_t fool = 0;
        if (fr.rest() == 1) {
            char new_buffer[1];
            fr.read(new_buffer, 1);
            fool = static_cast<unsigned char>(new_buffer[0]);
        } else {
            if (fr.eof()) {
                fool = static_cast<size_t>(8 + static_cast<unsigned char>(buffer[readed - 1]));
            }
        }
        std::vector<unsigned char> realText;
        for (size_t i = 0; i < readed; i++) {
            for (int j = 7; j >= 0; j--) {
                if ((buffer[i] & (1 << j)) != 0) {
                    realText.push_back(1);
                } else {
                    realText.push_back(0);
                }
            }
        }
        if (realText.size() < fool) {
            throw std::runtime_error("My code does not work, sorry");
        }
        realText.erase(realText.begin() + realText.size() - fool, realText.end());

        auto decoded = d.decode(realText);

        //for (auto i : decoded) std::cout << (char)i;
        char fw_buffer[fw.MAX_WRITE];
        size_t cnt = 0;
        for (unsigned char i : decoded) {
            fw_buffer[cnt] = i;
            cnt++;
            if (cnt == fw.MAX_WRITE) {
                cnt = 0;
                fw.write(fw_buffer, fw.MAX_WRITE);
            }
        }
        if (cnt) {
            fw.write(fw_buffer, cnt);
        }
    }

}
