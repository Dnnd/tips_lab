#ifndef LAB_TIPS_RECIEVER_H
#define LAB_TIPS_RECIEVER_H


#include "../huffman/Decoder.h"

class Reciever {
public:
  Reciever(const std::string &out_file, Decoder &decoder);

  void recieveAll();

private:
  std::vector<char> _in_buffer;
  std::string _out_file;
  Decoder &_decoder;
};


#endif //LAB_TIPS_RECIEVER_H
