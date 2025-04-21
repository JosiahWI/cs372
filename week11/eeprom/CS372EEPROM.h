#ifndef CS372EEPROM_H_INCLUDED
#define CS372EEPROM_H_INCLUDED

#include <cstdint>
#include <functional>

/**
 * Interface to the 24LC02B EEPROM.
 *
 * The class is implemented using the Arduino Wire object. If the lifetimes of
 * any two instances of this class overlap, the behavior is undefined.
 */
class CS372EEPROM {
public:
  CS372EEPROM();
  CS372EEPROM(CS372EEPROM const& other)            = delete;
  CS372EEPROM(CS372EEPROM&& other)                 = delete;
  CS372EEPROM& operator=(CS372EEPROM const& other) = delete;
  CS372EEPROM& operator=(CS372EEPROM&& other)      = delete;

  ~CS372EEPROM();

  /**
   * Write a value to the given address.
   *
   * There must be at least 5 milliseconds between each call to this method.
   *
   * @param addr Address (0-255) to write.
   * @param val Value to write.
   */
  void write_eeprom(std::uint8_t addr, std::uint8_t val);

  /** Read the value at the given address.
   *
   * @param addr Address to read.
   * @return Returns the value read from that address, or 0xff if the EEPROM
   * did not respond.
   */
  std::uint8_t read_eeprom(std::uint8_t addr);
};

#endif // CS372EEPROM_H_INCLUDED
