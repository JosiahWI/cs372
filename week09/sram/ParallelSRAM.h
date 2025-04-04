#ifndef PARALLEL_SRAM_H_INCLUDED
#define PARALLEL_SRAM_H_INCLUDED

#include <Arduino.h>

class ParallelSRAM {
public:
  ParallelSRAM(int* data_pins, int* addr_pins, int write_enable_pin,
               int output_enable_pin);

  ParallelSRAM(ParallelSRAM const& other)            = delete;
  ParallelSRAM& operator=(ParallelSRAM const& other) = delete;
  ParallelSRAM(ParallelSRAM&& other)                 = delete;
  ParallelSRAM& operator=(ParallelSRAM&& other)      = delete;

  ~ParallelSRAM();

  byte readSRAM(byte addr);
  void writeSRAM(byte addr, byte data);
};

#endif // PARALLEL_SRAM_H_INCLUDED
