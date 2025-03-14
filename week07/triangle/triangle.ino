#pragma GCC optimize "-O3"

#include "DACOscillate.h"
#include "types.h"

#include <array>
#include <cassert>
#include <cstdint>
#include <limits>
#include <vector>

template <int N>
constexpr std::array<DACChunk, N>
chunk_range() {
  static_assert(N <= std::numeric_limits<std::uint8_t>::max() + 1);

  std::array<DACChunk, N> result;
  for (int i{0}; i < N; ++i) {
    result[i] = DACChunk{static_cast<std::uint8_t>(i)};
  }
  return result;
}

namespace {
  constexpr auto voltage_line{chunk_range<256>()};
  auto g_DAC_pump{DACOscillate{voltage_line.begin(), voltage_line.end()}};
} // end anonymous namespace

void setup() {
}

void loop() {
  g_DAC_pump.step();
}

