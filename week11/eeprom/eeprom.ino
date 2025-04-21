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
  static int next_addr{0xa};
  static int num_corrected{0};
  if (next_addr <= 0xff) {
    std::uint8_t ah{eeprom.read_eeprom(next_addr)};
    std::uint8_t al{eeprom.read_eeprom(next_addr)};
    int          val{(ah << 8) | al};
    int          corrected_val{check_hamming(val)};
    if (val != corrected_val) {
      ++num_corrected;
      delay(5);
      eeprom.write_eeprom(next_addr, corrected_val);
    }
    ++next_addr;
  } else if (next_addr == 0x100) {
    ++next_addr;
    Serial.print(num_corrected);
  }
}
