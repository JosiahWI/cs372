#include "types.h"

#include <SPI.h>

#include <cstdint>

namespace {
  constexpr pin_t SS_PIN{10};
  constexpr pin_t MOSI_PIN{11};
  constexpr pin_t SCLK_PIN{13};
} // end anonymous namespace

struct SPIDataChunk
{
  std::uint8_t lo_byte;
  std::uint8_t hi_byte;
};

void setup() {
  // Skipped pinMode of 11 and 13 for now.
  pinMode(SS_PIN, OUTPUT);
  pinMode(MOSI_PIN, OUTPUT);
  pinMode(SCLK_PIN, OUTPUT);

  digitalWrite(SS_PIN, HIGH);

  SPI.begin();
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST);

  // For testing...
  digitalWrite(SS_PIN, LOW);
  SPI.transfer(0x38);
  SPI.transfer(0x00);
  digitalWrite(SS_PIN, HIGH);
}

void loop() {
}
