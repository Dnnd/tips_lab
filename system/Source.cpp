#include <iterator>
#include "Source.h"

Source::Source(const std::string &input_file, ChannelEncoder &encoder)
  : _encoder{encoder} {
  std::ifstream ifs{input_file};
  while (true) {
    char ch = ifs.get();
    if (ifs.good()) {
      _data.push_back(ch);
    } else {
      break;
    }
  }
}

void Source::transmitAll() {
  _encoder.setBuffer(std::move(_data));
  _encoder.transmit();
}

std::size_t Source::bufferSize() const {
  return _data.size();
}
