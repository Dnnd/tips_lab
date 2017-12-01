#include "Decoder.h"

Decoder::Decoder(Channel &channel, unsigned int symbol_len)
  : _channel{channel},
    _symbol_len{symbol_len} {

}

void Decoder::recieve() {

  auto[freq_table_size, success] = _channel.readInt();
  if (!success) {
    return;
  }

  HuffmanTree::FreqTable freqTable;
  for (unsigned i = 0; i < freq_table_size; ++i) {
    auto[freq, ok] = _channel.readInt();
    if (!ok) {
      return;
    }
    std::string res = _channel.readString(_symbol_len);
    freqTable[res] = freq;
  }

  HuffmanTree huffmanTree{std::move(freqTable)};
  auto[syms_count, ok] = _channel.readInt();
  if (!ok) {
    return;
  }
  auto iter = huffmanTree.root();
  for (std::size_t i = 0; i < syms_count && !_channel.isEmpty(); ++i) {
    while (!iter->isLeaf() && !_channel.isEmpty()) {
      auto bit = _channel.readBit();
      if (bit) {
        iter = iter->left();
      } else {
        iter = iter->right();
      }
    }
    for (auto ch : iter->symbol()) {
      _output_buffer.push_back(ch);
    }
    iter = huffmanTree.root();
  }
  this->_huffmanTree = std::move(huffmanTree);
}

std::vector<char> Decoder::extractBuffer() {
  return std::move(this->_output_buffer);
}
