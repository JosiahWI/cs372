#include "ParallelSRAM.h"

static ParallelSRAM* my_device{};

void
setup()
{
  int dataPins[] = {7, 8, 9, 10, 11, 23, 22, 21};
  int addrPins[] = {20, 19, 18, 17, 16, 15, 14, 13};
  my_device      = new ParallelSRAM(dataPins, addrPins, 5, 4);

  Serial.begin(9600);
  while (!Serial)
    ;
}

void
loop()
{
  static bool once{false};
  if (!once) {
    once = true;
    my_device->writeSRAM(0, 0xff);

    byte val = my_device->readSRAM(0);
    Serial.println(val);
  }
}
