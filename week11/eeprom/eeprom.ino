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
  static bool did_read{false};
  if (!did_read) {
    did_read = true;
    Serial.print(eeprom.read_eeprom(0xb));
  }
}
