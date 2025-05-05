#include "types.h"

#include <Arduino.h>

#include <array>
#include <csignal>

static IntervalTimer* get_g_step_timer();
static void           timer_handler();

namespace {
// In1, In2, In3, In4
constexpr pin_t STEPPER_PINS[]{22, 21, 19, 20};

using stepper_state_t = dig_t[4];
constexpr stepper_state_t STATE_ORDER[]{
    { LOW, HIGH,  LOW,  LOW},
    { LOW, HIGH,  LOW, HIGH},
    { LOW,  LOW,  LOW, HIGH},
    {HIGH,  LOW,  LOW, HIGH},
    {HIGH,  LOW,  LOW,  LOW},
    {HIGH,  LOW, HIGH,  LOW},
    { LOW,  LOW, HIGH,  LOW},
    { LOW, HIGH, HIGH,  LOW}
};
constexpr int total_states_per_rev{sizeof(STATE_ORDER) / sizeof(STATE_ORDER[0])};

std::sig_atomic_t volatile g_motor_step_interval_done;
} // end anonymous namespace

void
setup()
{
  IntervalTimer* step_timer{get_g_step_timer()};
  step_timer->begin(timer_handler, 800);
}

void
timer_handler()
{
  // Interrupts are disabled in hardware for this scope.
  //
  // (https://pjrc.com/teensy/interrupts.html)
  g_motor_step_interval_done = 1;
}

IntervalTimer*
get_g_step_timer()
{
  static IntervalTimer* step_timer{new IntervalTimer};
  return step_timer;
}

void
loop()
{
  static int stepper_state{0};
  // We do not have to disable interrupts here, because the state is of an
  // atomic type safe for access between signal handlers (it probably disables
  // interrupts in its implementation).
  if (g_motor_step_interval_done) {
    g_motor_step_interval_done = 0;
    for (int i = 0; i < 4; ++i) {
      digitalWrite(STEPPER_PINS[i], STATE_ORDER[stepper_state][i]);
    }
    ++stepper_state;
    if (total_states_per_rev == stepper_state) {
      stepper_state = 0;
    }
  }
}
