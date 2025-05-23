#include "types.h"

#include <Arduino.h>

#define lcd Serial2

static void wait_for_serial_ready(serial_t& serial);
static int  read_resistance();
static void show_resistance(int r);

namespace {
  constexpr pin_t POT_SENSOR_PIN{16};
  constexpr long long INPUT_MV{3440};
  constexpr long long MAX_INPUT_PIN_MV{3300};
  constexpr long long MAX_OUTPUT_MV{3000};
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

int
read_resistance()
{
  long long const level{static_cast<int>(analogRead(POT_SENSOR_PIN))};
  long long const mvolts{level * MAX_INPUT_PIN_MV / 1023};
  long long const mohms{
    (INPUT_MV - mvolts) * (POT_TOTAL_MOHM + R1_MOHM) / INPUT_MV - R1_MOHM};
  return static_cast<int>(mohms / 1000);
}

void
show_resistance(int r)
{
  lcd.write(LCD_COMMAND_MODE);
  lcd.write(LCD_COMMAND_CLR);
  lcd.write("R: ");
  lcd.print(r);
  lcd.write(LCD_OHM_SYMBOL);
}
