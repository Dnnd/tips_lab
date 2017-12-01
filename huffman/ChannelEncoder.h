#ifndef LAB_TIPS_CHANNEL_ENCODER
#define LAB_TIPS_CHANNEL_ENCODER


#include "../system/Channel.h"
#include "HuffmanTree.h"

enum class Encoding {
  Huffman,
  Uniform,
};

class ChannelEncoder {
public:
  ChannelEncoder(Channel &channel, unsigned symbol_len, Encoding enc = Encoding::Huffman);

  void setBuffer(std::vector<char> &&buffer);

  void transmit();

  unsigned symbolLen() const {
    return _symbol_len;
  }

private:
  std::vector<char> _input_buffer;
  unsigned _symbol_len;
  HuffmanTree _huffmanTree{};
  Encoding  _enc;
  Channel &_channel;
};


#endif //LAB_TIPS_CHANNEL_ENCODER
