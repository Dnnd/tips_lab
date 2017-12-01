#include <iostream>
#include <unordered_map>
#include "system/Channel.h"
#include "system/Source.h"
#include "huffman/Decoder.h"
#include "huffman/ChannelEncoder.h"
#include "system/Reciever.h"
#include "matrix/Matrix.h"
#include "system/AntiJammingEncoder.h"
#include "system/AntiJammingDecoder.h"
#include <tuple>


int main() {
  GaluaMatrix gen_matrix{
    std::vector<GaluaMatrix::RowType>{
      {1, 0, 0, 0, 1, 1, 1},
      {0, 1, 0, 0, 1, 1, 0},
      {0, 0, 1, 0, 1, 0, 1},
      {0, 0, 0, 1, 0, 1, 1},
    }};

  GaluaMatrix check_matrix{
    std::vector<GaluaMatrix::RowType>{
      {1, 1, 1},
      {1, 1, 0},
      {1, 0, 1},
      {0, 1, 1},
      {1, 0, 0},
      {0, 1, 0},
      {0, 0, 1},
    }};

  Channel coders_chan{};
  Channel decoders_chan{};
  Channel noise_chan{Noise{0.01}};

  ChannelEncoder encoder{coders_chan, 1, Encoding::Huffman};
  AntiJammingEncoder aj_encoder{gen_matrix, coders_chan, noise_chan};

  AntiJammingDecoder aj_decoder{check_matrix, noise_chan, decoders_chan};
  Decoder decoder{decoders_chan, 1};

  Source src{"../source.txt", encoder};
  Reciever reciever{"../dest.txt", decoder};

  std::size_t symbolsCount = src.bufferSize() / encoder.symbolLen();
  src.transmitAll();
  aj_encoder.transmitAll();

  aj_decoder.transmitAll();
  reciever.recieveAll();
  auto stats = noise_chan.getStats();
  const auto &aj_encoded = aj_encoder.getTransmited();
  const auto &aj_decoded = aj_decoder.getTransmited();

  std::size_t final_errors = 0;
  for (std::size_t i = 0; i < aj_encoded.size(); ++i) {
    final_errors += aj_encoded[i].diff(aj_decoded[i]);
  }

  std::size_t aj_corrected = aj_decoder.getErrCount();
  std::size_t corrupted = noise_chan.getErrCount();

  std::size_t fixed = corrupted - final_errors;
  std::size_t bad_fixed = aj_corrected - fixed;
  std::size_t not_fixed = corrupted - (fixed + bad_fixed);

  std::cout << "Total errors number: " << corrupted
            << "\nFixed errors: " << fixed
            << "\nNot fixed: " << not_fixed
            << "\nIncorrect fixes: " << bad_fixed;

  std::cout << "\nSymbols count: " << symbolsCount
            << "\nZeros count: " << stats.getZerosCount()
            << "\nOnes count: " << stats.getOnesCount()
            << "\nTotal bits: " << stats.getTotal()
            << "\nBit/symbol: " << stats.getAverageBitsPerSymbols(symbolsCount);
  return 0;
}