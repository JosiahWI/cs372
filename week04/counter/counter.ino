#include "debounce.h"
#include "display.h"
#include "types.h"

#include <Arduino.h>

#include <array>

static CS372Debounce*     get_g_button1();
static CS372Debounce*     get_g_button2();
static CS372SevenSegment* get_g_display();

namespace {
  constexpr pin_t BUTTON1_PIN{14};
  constexpr pin_t BUTTON2_PIN{15};
  constexpr pin_t DISPLAY_PINS[]{23, 22, 17, 18, 21, 20, 19};
} // end anonymous namespace


void
setup()
{
  get_g_button1();
  get_g_button2();
  get_g_display();
}

CS372Debounce*
get_g_button1()
{
  static CS372Debounce* button1{new CS372Debounce{BUTTON1_PIN}};
  return button1;
}

CS372Debounce*
get_g_button2()
{
  static CS372Debounce* button2{new CS372Debounce{BUTTON2_PIN}};
  return button2;
}

CS372SevenSegment*
get_g_display()
{
  static CS372SevenSegment* display{new CS372SevenSegment{DISPLAY_PINS}};
  return display;
}

void
loop()
{
  static int n{0};

  auto* button1{get_g_button1()};
  button1->update();
  if (button1->pressed() && n < 9) {
    get_g_display()->update(++n);
  }

  auto* button2{get_g_button2()};
  button2->update();
  if (button2->pressed() && n > 0) {
    get_g_display()->update(--n);
  }
}
