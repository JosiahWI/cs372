#include "kitt.h"

#include <Arduino.h>

namespace
{
  constexpr int LEDs_size{6};
  constexpr int LEDs[]{4, 5, 7, 12, 14, 17};
  unsigned long g_last_update{};
} // end anonymous namespace

static KITT* get_g_kitt();

void
setup()
{
  for (int pin : LEDs) {
    pinMode(pin, OUTPUT);
  }
  g_last_update = millis();
  // Initializes the global KITT instance.
  get_g_kitt();
}

KITT*
get_g_kitt()
{
  // This memory is intentionally left for the OS to free when the process
  // terminates. It doesn't have a trivial destructor, so for good practice
  // we want to make sure it can't be accessed after its lifetime ends.
  static KITT* kitt{new KITT{LEDs_size, LEDs}};
  return kitt;
}

void
loop()
{
  if (millis() - g_last_update > 100) {
    get_g_kitt()->update();
    g_last_update = millis();
  }
}
