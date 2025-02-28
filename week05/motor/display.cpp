#include "display.h"

#include <Arduino.h>

#include <cstring>

namespace {
  std::array<std::array<dig_t,7>,10> codes{
    std::array<dig_t,7>{HIGH,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW},
    std::array<dig_t,7>{HIGH, HIGH, HIGH,  LOW, HIGH, HIGH,  LOW},
    std::array<dig_t,7>{ LOW, HIGH,  LOW,  LOW,  LOW,  LOW, HIGH},
    std::array<dig_t,7>{ LOW, HIGH,  LOW,  LOW, HIGH,  LOW,  LOW},
    std::array<dig_t,7>{ LOW,  LOW, HIGH,  LOW, HIGH, HIGH,  LOW},
    std::array<dig_t,7>{ LOW,  LOW,  LOW, HIGH, HIGH,  LOW,  LOW},
    std::array<dig_t,7>{ LOW,  LOW,  LOW, HIGH,  LOW,  LOW,  LOW},
    std::array<dig_t,7>{HIGH, HIGH,  LOW,  LOW, HIGH, HIGH,  LOW},
    std::array<dig_t,7>{ LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW},
    std::array<dig_t,7>{ LOW,  LOW,  LOW,  LOW, HIGH,  LOW,  LOW},
  };
} // end anonymous namespace

CS372SevenSegment::CS372SevenSegment(pin_t const* pins)
{
  std::memcpy(this->display_pins.data(), pins,
              this->display_pins.size() * sizeof(pin_t));
  for (pin_t pin : this->display_pins) {
    pinMode(pin, OUTPUT);
  }
  this->update(0);
}

void
CS372SevenSegment::update(int n)
{
  if (n < 0 || n > 9) {
    return;
  }

  for (int i{0}; i < 7; ++i) {
    digitalWrite(this->display_pins[i], codes[n][i]);
  }
}
