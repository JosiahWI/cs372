#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED

#include "types.h"

class CS372SevenSegment
{
public:
  CS372SevenSegment(pin_t const* pins);
  void update(int n);

private:
  std::array<pin_t, 7> display_pins;
};

#endif // DISPLAY_H_INCLUDED
