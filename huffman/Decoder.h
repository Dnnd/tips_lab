#ifndef LAB_TIPS_DECODER_H
#define LAB_TIPS_DECODER_H


#include "../system/Channel.h"
#include "HuffmanTree.h"

class Decoder {
public:
  Decoder(Channel &channel, unsigned int symbol_len);

  void recieve();

  std::vector<char> extractBuffer();

private:
  std::vector<char> _output_buffer;
  unsigned _symbol_len;
  HuffmanTree _huffmanTree{};
  Channel &_channel;
};


#endif //LAB_TIPS_DECODER_H
