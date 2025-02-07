#ifndef KITT_H_INCLUDED
#define KITT_H_INCLUDED

#include <vector>

class KITT
{
public:
  /**
   * Constructor.
   *
   * @param LEDs_size: Length of LEDs.
   * @param LEDs: The pin numbers of the LEDs to use for printing the KITT
   *   pattern. The order of the pin numbers in the array will determine the
   *   order in which the pins light up.
   * @see update
   */
  KITT(int LEDs_size, int const* LEDs);

  // Defining a destructor is a requirement, otherwise we would not define
  // any of these explicitly for this class.
  ~KITT()                            = default;
  KITT(KITT const& other)            = default;
  KITT& operator=(KITT const& other) = default;
  KITT(KITT&& other)                 = default;
  KITT& operator=(KITT &&other)      = default;

  /**
   * Display the next frame of the KITT pattern.
   *
   * The pins will light up in the order they were specified, then reverse
   * order, then forward again, and so on. Each call to update will set the
   * previous pin in the order to off, and the next pin to on. Only those two
   * pins will be written per call.
   *
   * For each pin number that was provided to this object upon initialization,
   * its corresponding pin must be in OUTPUT mode or the behavior is undefined.
   *
   * Note that it is ok for the pin modes to change in-between calls as long as
   * they end up back in OUTPUT mode.
   */
  void update();
private:
  std::vector<int>                 pins;
  std::vector<int>::const_iterator it;
  enum {FORWARD, BACKWARD}         direction{FORWARD};

  // To prevent overrun, must not be called if pins is empty.
  void write_current_pin_unsafe(int value);
  void cycle_forward_unsafe();

  bool is_at_last_pin() const;
  void cycle_backward();
  bool is_at_first_pin() const;
};

#endif // KITT_H_INCLUDED
