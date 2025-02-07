#include <Arduino.h>

int g_next_LED_state{HIGH};

void
setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
}

void
loop()
{
  static unsigned long last_update{millis()};

  if (millis() - last_update > 1000) {
    digitalWrite(LED_BUILTIN, g_next_LED_state);
    if (g_next_LED_state == LOW) {
      g_next_LED_state = HIGH;
    } else {
      g_next_LED_state = LOW;
    }
    last_update = millis();
  }
}
