#ifndef DAC_OSCILLATE_H_INCLUDED
#define DAC_OSCILLATE_H_INCLUDED

#include <cassert>
#include <cstdint>
#include <iostream> // TODO remove
#include <iterator>

class DACChunk
{
public:
  constexpr DACChunk() : SPI_bytes{0, 0}
  {
  };
  constexpr DACChunk(std::uint8_t voltage_level)
    : SPI_bytes{static_cast<std::uint8_t>((voltage_level & 0x0f) << 4),
                static_cast<std::uint8_t>(0x30 | (voltage_level >> 4))}
  {
  };

  std::uint8_t
  get_low_byte() const
  {
    return this->SPI_bytes.lo_byte;
  }

  std::uint8_t
  get_high_byte() const
  {
    return this->SPI_bytes.hi_byte;
  }

private:
  struct SPIDataChunk
  {
    std::uint8_t lo_byte;
    std::uint8_t hi_byte;
  } SPI_bytes;
};

template<typename BidiIt>
class DACOscillate
{
public:
  DACOscillate(BidiIt start, BidiIt end)
    : start{start}, end{end}, it{start}
  {
    assert(start != end);
  }

  void step()
  {
    std::cout << static_cast<int>(this->it->get_high_byte()) << ' '
              << static_cast<int>(this->it->get_low_byte()) << '\n';
    std::advance(this->it, this->iterator_velocity);

    if (this->it == this->end) {
      this->iterator_velocity = -1;
      // We don't want to repeat the last element twice in a row,
      // unless it is also the first element.
      std::advance(this->it, -1);
      if (this->it != this->start) {
        std::advance(this->it, -1);
      }
    } 

    if (this->it == this->start) {
      this->iterator_velocity = 1;
    }

  }

private:
  BidiIt start;
  BidiIt end;
  BidiIt it;
  int    iterator_velocity{1};
};

#endif // DAC_OSCILLATE_H_INCLUDED
