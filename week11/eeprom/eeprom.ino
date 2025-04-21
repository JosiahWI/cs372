#include "cs372ecc.h"
#include "CS372EEPROM.h"

#include <Arduino.h>

static CS372EEPROM eeprom;

void
setup()
{
  Serial.begin(9600);
  while (!Serial) {}
}

void
loop()
{
  static int next_addr{0x0a};
  static int num_corrected{0};
  if (next_addr <= 0xff) {
    std::uint8_t ah{eeprom.read_eeprom(next_addr)};
    std::uint8_t al{eeprom.read_eeprom(next_addr + 1)};
    int          val{(ah << 8) | al};
    int          corrected_val{check_hamming(val)};
    if (val != corrected_val) {
      ++num_corrected;
      delay(5);
      eeprom.write_eeprom(next_addr, (corrected_val & 0xff00) >> 8);
      eeprom.write_eeprom(next_addr + 1, (corrected_val & 0x00ff));
    }
    next_addr += 2;
  } else if (next_addr == 0x100) {
    ++next_addr;
    Serial.print(num_corrected);
  }
}
