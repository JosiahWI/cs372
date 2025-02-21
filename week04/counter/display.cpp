#include "display.h"

#include <Arduino.h>

#include <cstring>

namespace {
  std::array<std::array<dig_t,7>,10> codes{
    std::array<dig_t,7>{ LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW},
    std::array<dig_t,7>{ LOW,  LOW,  LOW, HIGH,  LOW,  LOW, HIGH},
    std::array<dig_t,7>{HIGH,  LOW, HIGH, HIGH, HIGH, HIGH,  LOW},
    std::array<dig_t,7>{HIGH,  LOW, HIGH, HIGH,  LOW, HIGH, HIGH},
    std::array<dig_t,7>{HIGH, HIGH,  LOW, HIGH,  LOW,  LOW, HIGH},
    std::array<dig_t,7>{HIGH, HIGH, HIGH,  LOW,  LOW, HIGH, HIGH},
    std::array<dig_t,7>{HIGH, HIGH, HIGH,  LOW, HIGH, HIGH, HIGH},
    std::array<dig_t,7>{ LOW,  LOW, HIGH, HIGH,  LOW,  LOW, HIGH},
    std::array<dig_t,7>{HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH},
    std::array<dig_t,7>{HIGH, HIGH, HIGH, HIGH,  LOW, HIGH, HIGH},
  };
} // end anonymous namespace

CS372SevenSegment::CS372SevenSegment(pin_t const* pins)
{
  std::memcpy(this->display_pins.data(), pins,
              this->display_pins.size() * sizeof(pin_t));
  for (pin_t pin : this->display_pins) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
  }
}

void
CS372SevenSegment::update(int n)
{
  for (int i{0}; i < 7; ++i) {
    pinMode(this->display_pins[i], codes[n][i]);
  }
}
