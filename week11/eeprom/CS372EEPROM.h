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

  void         write_eeprom(std::uint8_t addr, std::uint8_t val);
  std::uint8_t read_eeprom(std::uint8_t addr);
};

#endif // CS372EEPROM_H_INCLUDED
