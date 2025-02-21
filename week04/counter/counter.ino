#include "debounce.h"
#include "types.h"

#include <Arduino.h>

#include <array>

static CS372Debounce* get_g_button1();

namespace {
  constexpr pin_t BUTTON1_PIN{2};
  constexpr std::array<pin_t, 7> display_pins{23, 22, 18, 17, 21, 20, 19};
} // end anonymous namespace


void
setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  for (pin_t pin : display_pins) {
    pinMode(pin, OUTPUT);
  }
  get_g_button1();
}

void
loop()
{
  auto* button{get_g_button1()};
  button->update();
  if (button->pressed()) {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  for (pin_t pin : display_pins) {
    digitalWrite(pin, HIGH);
  }
}

CS372Debounce*
get_g_button1()
{
  static CS372Debounce* button1{new CS372Debounce{BUTTON1_PIN}};
  return button1;
}
