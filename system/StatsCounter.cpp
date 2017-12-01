#include "StatsCounter.h"

void StatsCounter::count(bool bit) {
  if (bit) {
    ++_ones_counter;
  } else {
    ++_zeros_counter;
  }
}

size_t StatsCounter::getZerosCount() const {
  return _zeros_counter;
}

size_t StatsCounter::getOnesCount() const {
  return _ones_counter;
}

double StatsCounter::getAverageBitsPerSymbols(std::size_t symbols_count) const {
  return getTotal() / static_cast<double>(symbols_count);
}

std::size_t StatsCounter::getTotal() const {
  return _ones_counter + _zeros_counter;
}
