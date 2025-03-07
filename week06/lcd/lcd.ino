#include <Arduino.h>

#include <string_view>

#define lcd Serial2

using serial_t = decltype(lcd);

static void wait_for_serial_ready(serial_t& serial);

void
setup()
{
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
  static int done_display = 0;
  if (!done_display) {
    lcd.write("JV");
    done_display = 1;
  }
}
