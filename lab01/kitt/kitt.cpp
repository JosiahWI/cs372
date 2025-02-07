#include "kitt.h"

#include <Arduino.h>

KITT::KITT(int LEDs_size, int const* LEDs)
{
  this->pins.resize(LEDs_size);
  for (int i{0}; i < LEDs_size; ++i) {
    this->pins[i] = LEDs[i];
  }
  this->it = this->pins.begin();
}

void
KITT::update()
{
  if (this->pins.empty()) {
    return;
  }

  this->write_current_pin_unsafe(LOW);
  if (this->direction == FORWARD) {
    this->cycle_forward_unsafe();
  } else {
    this->cycle_backward();
  }
  this->write_current_pin_unsafe(HIGH);
}

void
KITT::write_current_pin_unsafe(int value)
{
  digitalWrite(*this->it, value);
}

void
KITT::cycle_forward_unsafe()
{
  if (this->is_at_last_pin()) {
    this->direction = BACKWARD;
  } else {
    ++this->it;
  }
}

bool
KITT::is_at_last_pin() const
{
  return (this->it + 1) == this->pins.end();
}

void
KITT::cycle_backward()
{
  if (this->is_at_first_pin()) {
    this->direction = FORWARD;
  } else {
    --this->it;
  }
}

bool
KITT::is_at_first_pin() const
{
  return this->it == this->pins.begin();
}
