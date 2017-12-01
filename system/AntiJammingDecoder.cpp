#include "AntiJammingDecoder.h"

AntiJammingDecoder::AntiJammingDecoder(GaluaMatrix matrix, Channel &in, Channel &out)
  : _check_matrix{std::move(matrix)},
    _in{in},
    _out{out} {

}

void AntiJammingDecoder::fix(GaluaMatrix &word, GaluaMatrix &syndrome) {
  for (std::size_t i = 0; i < _check_matrix.rowsNumber(); ++i) {
    bool is_equal = true;
    for (std::size_t j = 0; is_equal && j < _check_matrix.colsNumber(); ++j) {
      if (_check_matrix[i][j] != syndrome[0][j]) {
        is_equal = false;
      }
    }
    if (is_equal) {
      word[0][i] = !word[0][i];
      return;;
    }
  }
}

void AntiJammingDecoder::transmit() {
  std::size_t word_len = _check_matrix.rowsNumber();
  GaluaMatrix word{1, word_len};

  if (_in.size() < word_len) {
    return;
  }
  for (std::size_t i = 0; i < word_len; ++i) {
    word[0][i] = _in.readBit();
  }
  GaluaMatrix syndrome = word * _check_matrix;
  bool is_error = false;
  for (std::size_t i = 0; i < syndrome.colsNumber(); ++i) {
    if (syndrome[0][i] != false) {
      is_error = true;
    }
  }
  if (is_error) {
    fix(word, syndrome);
    ++err_count;
  };
  _transmited.push_back(word);

  for (std::size_t i = 0; i < word_len - _check_matrix.colsNumber(); ++i) {
    _out.writeBit(word[0][i]);
  }

}

void AntiJammingDecoder::transmitAll() {
  while (_in.size() >= _check_matrix.rowsNumber() - _check_matrix.colsNumber()) {
    transmit();
  }

}

const std::vector<GaluaMatrix> &AntiJammingDecoder::getTransmited() const {
  return _transmited;
}

std::size_t AntiJammingDecoder::getErrCount() const {
  return err_count;
}
