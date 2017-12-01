#ifndef LAB_TIPS_NOISE_H
#define LAB_TIPS_NOISE_H

#include <random>
#include <iostream>

class Noise {
public:
  explicit Noise(double probability);
  bool makeNoise(bool bit);
  std::size_t getErrCount();
private:
  std::size_t err_count;
  std::default_random_engine _generator;
  std::bernoulli_distribution _distribution;
};


#endif //LAB_TIPS_NOISE_H
