#pragma GCC optimize "-O3"

#include "DACOscillate.h"
#include "types.h"

#include <cassert>
#include <cstdint>
#include <limits>
#include <vector>

static std::vector<DACChunk> chunk_range(int n);

namespace {
  auto voltage_line{chunk_range(256)};
  auto g_DAC_pump{DACOscillate{voltage_line.begin(), voltage_line.end()}};
} // end anonymous namespace

void setup() {
}

void loop() {
  g_DAC_pump.step();
}

std::vector<DACChunk>
chunk_range(int n) {
  assert(n <= std::numeric_limits<std::uint8_t>::max() + 1);

  std::vector<DACChunk> result;
  result.resize(n);
  for (int i{0}; i < n; ++i) {
    result[i] = DACChunk{static_cast<std::uint8_t>(i)};
  }
  return result;
}
