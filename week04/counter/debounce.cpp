#include "debounce.h"

#include <Arduino.h>

CS372Debounce::CS372Debounce(pin_t pin) : button_pin{pin}
{
  pinMode(this->button_pin, INPUT);
}

void
CS372Debounce::update()
{
  int const pin_state{digitalRead(this->button_pin)};

  if (DOWN == this->button_state) {
    if (DOWN == pin_state) {
      ++this->count;
    } else {
      this->count = 0;
    }
    if (this->count > this->threshold) {
      this->button_state = UP;
      this->count        = 0;
    }
  } else {
    if (UP == pin_state) {
      ++this->count;
    } else {
      this->count = 0;
    }
    if (count > threshold) {
      this->button_state    = DOWN;
      this->count           = 0;
      this->press_available = true;
    }
  }
}

bool
CS372Debounce::pressed()
{
  bool result{this->press_available};
  this->press_available = false;
  return result;
}
