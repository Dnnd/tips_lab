#ifndef LAB_TIPS_ANTIJAMMINGENCODER_H
#define LAB_TIPS_ANTIJAMMINGENCODER_H


#include "../matrix/Matrix.h"
#include "Channel.h"

class AntiJammingEncoder {
public:
  explicit AntiJammingEncoder(const GaluaMatrix &matrix, Channel &_in, Channel &_out);

  void transmit(std::size_t word_size);

  void transmitAll();

  const std::vector<GaluaMatrix> &getTransmited() const;

private:
  std::vector<GaluaMatrix> _transmited;
  GaluaMatrix _gen_matrix;
  Channel &_out;
  Channel &_in;
};


#endif //LAB_TIPS_ANTIJAMMINGENCODER_H
