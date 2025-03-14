#include "DACOscillate.h"

#include <array>
#include <cstdint>
#include <limits>

template<int N>
static constexpr std::array<DACChunk, N>
chunk_range() {
  static_assert(N <= std::numeric_limits<std::uint8_t>::max() + 1);

  std::array<DACChunk, N> result;
  for (int i{0}; i < N; ++i) {
    result[i] = DACChunk{static_cast<std::uint8_t>(i)};
  }
  return result;
}

int
main()
{
  constexpr auto voltage_line = chunk_range<4>();
  auto DAC_pump{DACOscillate{voltage_line.begin(), voltage_line.end()}};

  DAC_pump.step();
  DAC_pump.step();
  DAC_pump.step();
  DAC_pump.step();
  DAC_pump.step();
  DAC_pump.step();
  DAC_pump.step();
  DAC_pump.step();

  return 0;
}
