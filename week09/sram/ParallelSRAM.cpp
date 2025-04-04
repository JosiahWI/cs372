#include "ParallelSRAM.h"

#include <Arduino.h>

ParallelSRAM::ParallelSRAM(int* data_pins, int* addr_pins, int write_enable_pin,
                           int output_enable_pin)
{
}

ParallelSRAM::~ParallelSRAM()
{
}

byte
ParallelSRAM::readSRAM(byte addr)
{
  return 0;
}

void
ParallelSRAM::writeSRAM(byte addr, byte data)
{
}
