#ifndef LAB_TIPS_CHANNEL_H
#define LAB_TIPS_CHANNEL_H


#include <cstddef>
#include <iostream>
#include "../Noise.h"
#include "StatsCounter.h"

class Channel {
public:
  static const unsigned BYTE_SIZE = 8;

  explicit Channel(const Noise &noise_source = Noise{0});

  void writeBit(bool bit);

  bool readBit();

  std::size_t size();

  void writeByte(char byte);

  std::pair<char, bool> readByte();

  void writeInt(int number);

  std::pair<int, bool> readInt();

  void writeCode(const std::vector<bool> &code);

  void writeString(const std::string &str);

  std::string readString(std::size_t len);

  bool isEmpty();

  const StatsCounter &getStats() const;

  void flush();

  std::size_t getErrCount() {
    return _noise_source.getErrCount();
  }

private:
  StatsCounter _stats;
  Noise _noise_source;
  std::size_t _rpos;
  std::vector<bool> _channel;
};


#endif //LAB_TIPS_CHANNEL_H
