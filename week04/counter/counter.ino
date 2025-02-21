#include "debounce.h"
#include "types.h"

#include <Arduino.h>

static CS372Debounce* get_g_button1();

namespace {
  constexpr pin_t BUTTON1_PIN{2};
} // end anonymous namespace


void
setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
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
}

CS372Debounce*
get_g_button1()
{
  static CS372Debounce* button1{new CS372Debounce{BUTTON1_PIN}};
  return button1;
}
