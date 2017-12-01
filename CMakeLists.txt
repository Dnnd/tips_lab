cmake_minimum_required(VERSION 3.8)
project(lab_tips)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp huffman/Decoder.cpp huffman/Decoder.h system/Channel.cpp system/Channel.h system/Source.cpp system/Source.h system/Reciever.cpp system/Reciever.h Noise.cpp Noise.h huffman/HuffmanTree.cpp huffman/HuffmanTree.h huffman/HuffmanTreeNode.cpp huffman/HuffmanTreeNode.h huffman/ChannelEncoder.cpp huffman/ChannelEncoder.h system/StatsCounter.cpp system/StatsCounter.h matrix/Matrix.h system/AntiJammingEncoder.cpp system/AntiJammingEncoder.h matrix/Matrix.cpp system/AntiJammingDecoder.cpp system/AntiJammingDecoder.h)
add_executable(lab_tips ${SOURCE_FILES})