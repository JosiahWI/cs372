#include "hall_effect.h"
#include "types.h"

#include <Arduino.h>

#include <csignal>

static void button_interrupt_handler();
static HallEffect* get_g_hall_effect();
static void handle_button_state();

namespace {
  constexpr pin_t BUTTON_PIN{20};
} // end anonymous namespace

volatile std::sig_atomic_t g_button_press_counter = 0;

void
setup()
{
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), button_interrupt_handler, FALLING);

  Serial.begin(9600);
  while (!Serial) {};
  // Make sure global HallEffect object is initialized now.
  if (get_g_hall_effect()->is_failed()) {
    Serial.println("Failed to detect slave device.");
  } else {
    Serial.println("Found slave device.");
  }
}

void
loop()
{
  handle_button_state();
  get_g_hall_effect()->handle_continue();
  if (get_g_hall_effect()->has_fresh_value()) {
    Serial.println(get_g_hall_effect()->get_value());
  }
}

void
handle_button_state()
{
  if (g_button_press_counter > 0) {
    --g_button_press_counter;
      get_g_hall_effect()->start_reading();
  }
}

void
button_interrupt_handler()
{
  cli();
  ++g_button_press_counter;
  sei();
}

HallEffect*
get_g_hall_effect()
{
  static HallEffect* hall_effect{new HallEffect{}};
  return hall_effect;
}
