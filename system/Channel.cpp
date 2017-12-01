#include "Channel.h"

Channel::Channel(const Noise &noise_source)
  : _noise_source{noise_source},
    _rpos{0} {

}

void Channel::writeBit(bool bit) {
  bool to_transmit = _noise_source.makeNoise(bit);
//  std::cout << to_transmit;
  _channel.push_back(to_transmit);
  _stats.count(to_transmit);
}

bool Channel::readBit() {
  return _channel[_rpos++];
}

void Channel::writeByte(char byte) {
  for (unsigned i = 0; i < BYTE_SIZE; ++i) {
    writeBit(byte & 1);
    byte = byte >> 1;
  }
}

std::pair<char, bool> Channel::readByte() {
  if (_channel.size() < BYTE_SIZE) {
    return {'\0', false};
  }
  char byte = 0;
  for (unsigned i = 0; i < BYTE_SIZE; ++i) {
    int bit = (_channel[_rpos++]) ? 1 : 0;
    byte += (1 << i) * bit;
  }
  return {byte, true};
}

std::pair<int, bool> Channel::readInt() {
  if (_channel.size() < BYTE_SIZE * sizeof(int) || _rpos + sizeof(int) >= _channel.size()) {
    return {0, false};
  }

  int number = 0;
  for (unsigned i = 0; i < BYTE_SIZE * sizeof(int); ++i) {
    int bit = (_channel[_rpos++]) ? 1 : 0;
    number += (1 << i) * bit;
  }
  return {number, true};
}

void Channel::writeInt(int number) {
  for (unsigned i = 0; i < sizeof(number) * BYTE_SIZE; ++i) {
    writeBit(number & 1);
    number = number >> 1;
  }
}

bool Channel::isEmpty() {
  return _rpos == _channel.size();
}

void Channel::writeCode(const std::vector<bool> &code) {
  for (auto i: code) {
    writeBit(i);
  }
}

void Channel::writeString(const std::string &str) {
  for (auto ch :str) {
    writeByte(ch);
  }
}

std::string Channel::readString(std::size_t len) {
  std::string buff;
  buff.reserve(len);
  for (std::size_t i = 0; i < len; ++i) {
    auto[sym, ok] = readByte();
    if (!ok) {
      return "";
    }
    buff.push_back(sym);
  }
  return std::move(buff);
}

const StatsCounter &Channel::getStats() const {
  return _stats;
}

void Channel::flush() {
  _channel.erase(_channel.begin(), _channel.begin() + _rpos);
  _rpos = 0;
}

std::size_t Channel::size() {
  return _channel.size() - _rpos;
}
