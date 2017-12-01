#include "Reciever.h"
#include <fstream>

void Reciever::recieveAll() {
  _decoder.recieve();
  this->_in_buffer = std::move(_decoder.extractBuffer());
  std::ofstream ofs{_out_file};
  for (auto ch : _in_buffer) {
    ofs << ch;
  }
}

Reciever::Reciever(const std::string &out_file, Decoder &decoder)
  : _out_file{out_file},
    _decoder{decoder} {
}
