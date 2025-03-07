#include "types.h"

#include <Arduino.h>

#define lcd Serial2

static void wait_for_serial_ready(serial_t& serial);
static long read_resistance();
static void show_resistance(long r);

namespace {
  constexpr pin_t POT_SENSOR_PIN{16};
  constexpr int       INPUT_MV{3300};
  constexpr int       MAX_OUTPUT_MV{3000};
  constexpr long long R1_MOHM{2200000};
  constexpr long long POT_TOTAL_MOHM{10000000};
  constexpr int       LCD_OHM_SYMBOL{0b11110100};
  constexpr int       LCD_COMMAND_MODE{0xfe};
  constexpr int       LCD_COMMAND_CLR{0x01};
} // end anonymous namespace

void
setup()
{
  pinMode(POT_SENSOR_PIN, INPUT);
  Serial2.begin(9600);
  wait_for_serial_ready(lcd);
}

void
wait_for_serial_ready(serial_t& serial)
{
  while (!serial);
}

void
loop()
{
  show_resistance(read_resistance());
}

long
read_resistance()
{
  int const  level{static_cast<int>(analogRead(POT_SENSOR_PIN))};
  int const  mvolts{1000 * level * MAX_OUTPUT_MV / 1023};
  long const mohms{static_cast<long>(
    (mvolts * (POT_TOTAL_MOHM + R1_MOHM) - INPUT_MV * R1_MOHM) /
    (INPUT_MV - mvolts))};
  return mohms;
}

void
show_resistance(long r)
{
  lcd.write(LCD_COMMAND_MODE);
  lcd.write(LCD_COMMAND_CLR);
  lcd.print(r);
  lcd.write(LCD_OHM_SYMBOL);
}
