#ifndef DEBOUNCE_H_INCLUDED
#define DEBOUNCE_H_INCLUDED

#include "types.h"

class CS372Debounce
{
public:
  CS372Debounce(pin_t pin);

  void update();
  bool pressed();
private:
  pin_t button_pin;
  int   count{0};

  enum ButtonState : dig_t {
    UP   = HIGH,
    DOWN = LOW,
    MAX_STATE,
  } button_state;

  bool press_available{false};

  static constexpr int threshold{10000};
};

#endif // DEBOUNCE_H_INCLUDED
