cmake_minimum_required(VERSION 3.9)
project(haffmun)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
add_executable(haffmun util/main.cpp lib/huffman_tree.h lib/huffman_tree.cpp lib/encoder.h util/file_writer.h util/file_writer.cpp util/file_reader.h util/file_reader.cpp lib/encoder.cpp lib/decoder.h lib/decoder.cpp util/compressor.h util/compressor.cpp util/decompressor.h util/decompressor.cpp)