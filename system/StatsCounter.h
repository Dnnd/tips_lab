#ifndef LAB_TIPS_STATSCOUNTER_H
#define LAB_TIPS_STATSCOUNTER_H

#include <unordered_map>

class StatsCounter {
public:
  void count(bool bit);

  size_t getZerosCount() const;

  size_t getOnesCount() const;

  double getAverageBitsPerSymbols(std::size_t symbols_count) const;

  std::size_t getTotal() const;


private:
  std::size_t _ones_counter{0};
  std::size_t _zeros_counter{0};
};


#endif //LAB_TIPS_STATSCOUNTER_H
