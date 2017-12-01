#ifndef LAB_TIPS_SOURCE_H
#define LAB_TIPS_SOURCE_H


#include <vector>
#include <string>
#include <fstream>
#include "Channel.h"
#include "../huffman/ChannelEncoder.h"

class Source {
public:
  Source(const std::string &input_file, ChannelEncoder &encoder);

  void transmitAll();
  std::size_t bufferSize() const;
private:
  std::vector<char> _data;
  ChannelEncoder &_encoder;
};


#endif //LAB_TIPS_SOURCE_H
