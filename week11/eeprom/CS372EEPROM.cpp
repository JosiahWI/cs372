#include "CS372EEPROM.h"

#include <Wire.h>

#include <array>
#include <cassert>
#include <cstdint>
#include <functional>
#include <string>

namespace {
constexpr int chip_address{0x50};
} // end anonymous namespace

CS372EEPROM::CS372EEPROM()
{
  Wire.begin();
}

CS372EEPROM::~CS372EEPROM()
{
  Wire.end();
}

void
CS372EEPROM::write_eeprom(std::uint8_t addr, std::uint8_t val)
{
}

std::uint8_t
CS372EEPROM::read_eeprom(std::uint8_t addr)
{
  Wire.beginTransmission(chip_address);
  Wire.write(addr);
  Wire.endTransmission();
  Wire.requestFrom(chip_address, 1);
  while (1 != Wire.available()) {}
  return Wire.read();

  return 0;
}
