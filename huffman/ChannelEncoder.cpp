#include "ChannelEncoder.h"

#include <unordered_map>

ChannelEncoder::ChannelEncoder(Channel &channel, unsigned symbol_len, Encoding enc)
  : _channel(channel),
    _symbol_len{symbol_len},
    _enc{enc},
    _huffmanTree{},
    _input_buffer{} {
}

void ChannelEncoder::transmit() {
  HuffmanTree::FreqTable freqTable;
  std::string sym;
  sym.resize(_symbol_len);
  for (std::size_t i = 0; i < _input_buffer.size(); i += _symbol_len) {
    for (unsigned j = 0; j < _symbol_len; ++j) {
      sym[j] = _input_buffer[i + j];
    }
    ++freqTable[sym];
  }

  _channel.writeInt(freqTable.size());
  std::size_t sym_count = 0;
  HuffmanTree::FreqTable normalized_freq_table;
  for (auto[symbol, freq] : freqTable) {
    sym_count += freq;
    if (_enc == Encoding::Huffman) {
      _channel.writeInt(freq);
      normalized_freq_table[symbol] = freq;
    } else {
      _channel.writeInt(1);
      normalized_freq_table[symbol] = 1;
    }
    _channel.writeString(symbol);
  }

  _channel.writeInt(sym_count);
  HuffmanTree huffmanTree{std::move(normalized_freq_table)};

  for (std::size_t i = 0; i < _input_buffer.size(); i += _symbol_len) {
    for (unsigned j = 0; j < _symbol_len; ++j) {
      sym[j] = _input_buffer[i + j];
    }
    auto code = huffmanTree.getCodeBySymbol(sym);
    _channel.writeCode(code);
  }
  _huffmanTree = std::move(huffmanTree);
}

void ChannelEncoder::setBuffer(std::vector<char> &&buffer) {
  _input_buffer = std::move(buffer);
  buffer.clear();
}

