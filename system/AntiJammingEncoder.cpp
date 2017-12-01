#include "AntiJammingEncoder.h"

AntiJammingEncoder::AntiJammingEncoder(const GaluaMatrix &matrix, Channel &in, Channel &out)
  : _gen_matrix{matrix},
    _out{out},
    _in{in} {
}

void AntiJammingEncoder::transmit(std::size_t word_size) {
  GaluaMatrix word{1, word_size};
  if (_in.size() < word_size) {
    return;
  }
  for (std::size_t i = 0; i < word_size; ++i) {
    word[0][i] = _in.readBit();
  }
  GaluaMatrix result = word * _gen_matrix;
  _transmited.push_back(result);

  for (std::size_t i = 0; i < result[0].size(); ++i) {
    _out.writeBit(result[0][i]);
  }
}

void AntiJammingEncoder::transmitAll() {
  std::size_t word_size = _gen_matrix.rowsNumber();
  while (_in.size() >= word_size) {
    transmit(word_size);
  }
}

const std::vector<GaluaMatrix> &AntiJammingEncoder::getTransmited() const {
  return _transmited;
}
