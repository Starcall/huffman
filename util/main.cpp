#include <iostream>
#include "../lib/huffman_tree.h"
#include "../lib/encoder.h"
#include "../lib/decoder.h"
#include "compressor.h"
#include "decompressor.h"
#include <ctime>
int main(int argc, char* argv[]) {
    if (argc == 2) {
        if ((std::string)argv[1] == "-h") {
            std::cout << "Program arguments -e to encode, -d to decode\n";
        } else {
            std::cout << "No such options. Type -h to see usage\n";
        }
        return 0;
    }
    if (argc != 4) {
        std::cout << "No such options. Type -h to see usage\n";
    } else {
        try {
            if ((std::string)argv[1] == "-e") {
                compressor Compress(argv[2]);
                double curTime = std::clock();
                Compress.compress(argv[3]);
                std::cout << "Done in: " << std::fixed << 1.0 * (std::clock() - curTime) / CLOCKS_PER_SEC << std::endl;
            }
            else if ((std::string)argv[1] == "-d") {
                decompressor Decompress(argv[2]);
                double curTime = std::clock();
                Decompress.decompress(argv[3]);
                std::cout << "Done in: " << std::fixed << 1.0 * (std::clock() - curTime) / CLOCKS_PER_SEC << std::endl;
            } else {
                std::cout << "No such options. Type -h to see usage\n";
            }
        } catch (std::runtime_error e) {
            std::cout << "Oups, error " << e.what() << std::endl;
        }
    }
    return 0;
}
