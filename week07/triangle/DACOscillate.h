#ifndef DAC_OSCILLATE_H_INCLUDED
#define DAC_OSCILLATE_H_INCLUDED

#include "types.h"

#include <Arduino.h>
#include <SPI.h>

#include <cassert>
#include <cstdint>
#include <iterator>

class DACChunk
{
public:
  constexpr DACChunk() : SPI_bytes{0, 0}
  {
  }

  constexpr DACChunk(std::uint8_t voltage_level)
    : SPI_bytes{static_cast<std::uint8_t>((voltage_level & 0x0f) << 4),
                static_cast<std::uint8_t>(0x30 | (voltage_level >> 4))}
  {
  }

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

    pinMode(SS_PIN, OUTPUT);
    pinMode(MOSI_PIN, OUTPUT);
    pinMode(SCLK_PIN, OUTPUT);

    digitalWrite(SS_PIN, HIGH);

    SPI.begin();
    SPI.setDataMode(SPI_MODE0);
    SPI.setBitOrder(MSBFIRST);
  }

  void step()
  {
    this->send(*this->it);
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
  void
  send(DACChunk const& chunk)
  {
    digitalWrite(SS_PIN, LOW);
    SPI.transfer(chunk.get_high_byte());
    SPI.transfer(chunk.get_low_byte());
    digitalWrite(SS_PIN, HIGH);
  }

  BidiIt start;
  BidiIt end;
  BidiIt it;
  int    iterator_velocity{1};

  static constexpr pin_t SS_PIN{10};
  static constexpr pin_t MOSI_PIN{11};
  static constexpr pin_t SCLK_PIN{13};
};

#endif // DAC_OSCILLATE_H_INCLUDED
