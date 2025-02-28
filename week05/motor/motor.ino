#include "debounce.h"
#include "display.h"
#include "types.h"

#include <Arduino.h>

#include <array>

static CS372Debounce*     get_g_button1();
static CS372Debounce*     get_g_button2();
static CS372SevenSegment* get_g_display();
static void               loop_motor();
static int                step_motor_state();

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
  digitalWrite(MOTOR_IN1_PIN, LOW);
  digitalWrite(MOTOR_IN2_PIN, HIGH);
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
  static int _run{0};
  auto* button1{get_g_button1()};
  button1->update();
  if (button1->pressed()) {
    _run = 1;
  }

  auto* button2{get_g_button2()};
  button2->update();
  if (button2->pressed()) {
    _run = 0;
  }

  if (_run) {
    loop_motor();
  }
}

void
loop_motor()
{
  static auto last_update{millis()};
  static auto _hold{0};

  if (_hold && (millis() - last_update > 50000)) {
    _hold = step_motor_state();
    last_update = millis();
  } else if (!_hold && (millis() - last_update > 20)) {
    _hold = step_motor_state();
    last_update = millis();
  }
}

int
step_motor_state()
{
  static int n{0};
  static int accel{1};
  static int rotation_state{0};

  get_g_display()->update(n / 26);

  if (1 == accel) {
    analogWrite(MOTOR_ENABLE_PIN, n++);
    if (255 == n) {
      accel = 0;
      return 1;
    }
  } else {
    analogWrite(MOTOR_ENABLE_PIN, n--);
    if (0 == n) {
      accel = 1;
      if (0 == rotation_state) {
        digitalWrite(MOTOR_IN1_PIN, LOW);
        digitalWrite(MOTOR_IN2_PIN, HIGH);
        rotation_state = 1;
      } else {
        digitalWrite(MOTOR_IN1_PIN, HIGH);
        digitalWrite(MOTOR_IN2_PIN, LOW);
        rotation_state = 0;
      }
    }
  }
  return 0;
}
