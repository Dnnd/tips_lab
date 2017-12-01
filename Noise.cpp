#include "Noise.h"

Noise::Noise(double probability)
  : _generator{},
    _distribution{probability} {

}

bool Noise::makeNoise(bool bit) {
  bool is_corrupted = _distribution(_generator);
  if (is_corrupted) {
    ++err_count;
  }
  return is_corrupted == !bit;
}

std::size_t Noise::getErrCount() {
  return err_count;
}
