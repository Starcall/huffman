cmake_minimum_required(VERSION 2.8)

project(HUFFMAN)

include_directories(${HUFFMAN_SOURCE_DIR})

add_executable(main
        util/main.cpp
        util/compressor.cpp
        util/compressor.h
        util/decompressor.h
        util/decompressor.cpp
        util/file_reader.cpp
        util/file_reader.h
        util/file_writer.cpp
        util/file_writer.h
        lib/huffman_tree.cpp
        lib/huffman_tree.h
        lib/encoder.cpp
        lib/decoder.cpp
        lib/encoder.h
        lib/decoder.h
        )

add_executable(testing
        gtest/gtest-all.cc
        gtest/gtest.h
        gtest/gtest_main.cc
        test/testing.cpp
        util/compressor.cpp
        util/compressor.h
        util/decompressor.h
        util/decompressor.cpp
        util/file_reader.cpp
        util/file_reader.h
        util/file_writer.cpp
        util/file_writer.h
        lib/huffman_tree.cpp
        lib/huffman_tree.h
        lib/encoder.cpp
        lib/decoder.cpp
        lib/encoder.h
        lib/decoder.h
        )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -pedantic")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -std=c++11 -fsanitize=address,undefined -D_GLIBCXX_DEBUG")


target_link_libraries(main -lpthread)
target_link_libraries(testing -lpthread)