#ifndef PARALLEL_SRAM_H_INCLUDED
#define PARALLEL_SRAM_H_INCLUDED

#include <array>

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

private:
  static constexpr int data_bus_width{8};
  static constexpr int addr_bus_width{8};

  std::array<int, data_bus_width> data_pins;
  std::array<int, addr_bus_width> addr_pins;
  int                             write_enable_pin;
  int                             output_enable_pin;

  void          write_addr(byte addr);
  void          enable_read();
  unsigned long read_ulong();
};

#endif // PARALLEL_SRAM_H_INCLUDED
