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
  constexpr pin_t MOTOR_ENABLE_PIN{12};
  constexpr pin_t MOTOR_IN1_PIN{10};
  constexpr pin_t MOTOR_IN2_PIN{11};
} // end anonymous namespace


void
setup()
{
  get_g_button1();
  get_g_button2();
  get_g_display();
  pinMode(MOTOR_ENABLE_PIN, OUTPUT);
  pinMode(MOTOR_IN1_PIN, OUTPUT);
  pinMode(MOTOR_IN2_PIN, OUTPUT);
  digitalWrite(MOTOR_IN1_PIN, HIGH);
  digitalWrite(MOTOR_IN2_PIN, LOW);
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
  auto* button1{get_g_button1()};
  button1->update();
  if (button1->pressed()) {
    get_g_display()->update(6);
    digitalWrite(MOTOR_ENABLE_PIN, HIGH);
  }

  auto* button2{get_g_button2()};
  button2->update();
  if (button2->pressed()) {
    get_g_display()->update(9);
    digitalWrite(MOTOR_ENABLE_PIN, LOW);
  }
}
