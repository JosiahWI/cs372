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
  static bool did_oneshot{false};
  if (!did_oneshot) {
    did_oneshot = true;
    eeprom.write_eeprom(0x0, 0xff);
    delay(10);
    Serial.print(eeprom.read_eeprom(0x0));
  }
}
