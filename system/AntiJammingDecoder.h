#ifndef LAB_TIPS_ANTIJAMMINGDECODER_H
#define LAB_TIPS_ANTIJAMMINGDECODER_H


#include <utility>
#include <algorithm>
#include "Channel.h"
#include "../matrix/Matrix.h"

class AntiJammingDecoder {
public:
  explicit AntiJammingDecoder(GaluaMatrix matrix, Channel &in, Channel &out);

  void fix(GaluaMatrix &word, GaluaMatrix &syndrome);

  void transmit();

  void transmitAll();

  const std::vector<GaluaMatrix> &getTransmited() const;

  std::size_t getErrCount() const;

private:
  std::size_t err_count{0};

  std::vector<GaluaMatrix> _transmited;
  GaluaMatrix _check_matrix;
  Channel &_in;
  Channel &_out;
};


#endif //LAB_TIPS_ANTIJAMMINGDECODER_H
