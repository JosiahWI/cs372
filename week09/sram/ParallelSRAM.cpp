#include "ParallelSRAM.h"

#include <Arduino.h>

#include <cstring>
#include <bitset>

ParallelSRAM::ParallelSRAM(int* data_pins, int* addr_pins, int write_enable_pin,
                           int output_enable_pin)
    : write_enable_pin{write_enable_pin}, output_enable_pin{output_enable_pin}
{
  std::memcpy(this->data_pins.data(), data_pins, this->data_pins.size());
  std::memcpy(this->addr_pins.data(), addr_pins, this->data_pins.size());

  // The data pins must be in INPUT mode (or we have a very big problem),
  // and we must keep them in INPUT mode until writing.

  for (int addr_pin : this->addr_pins) {
    pinMode(addr_pin, OUTPUT);
  }

  pinMode(this->write_enable_pin, OUTPUT);
  pinMode(this->output_enable_pin, OUTPUT);
}

ParallelSRAM::~ParallelSRAM()
{
}

byte
ParallelSRAM::readSRAM(byte addr)
{
  this->write_addr(addr);
  this->enable_read();
  return static_cast<byte>(this->read_ulong());
}

void
ParallelSRAM::writeSRAM(byte addr, byte data)
{
}

void
ParallelSRAM::write_addr(byte addr)
{
  using pin_array_size_t = decltype(this->addr_pins)::size_type;

  std::bitset<addr_bus_width> addr_bits{addr};
  for (pin_array_size_t i{0}; i < this->addr_pins.size(); ++i) {
    digitalWrite(this->addr_pins[i], addr_bits[i]);
  }
}

void
ParallelSRAM::enable_read()
{
  for (int data_pin : this->data_pins) {
    pinMode(data_pin, INPUT);
  }
  digitalWrite(this->output_enable_pin, HIGH);
}

unsigned long
ParallelSRAM::read_ulong()
{
  using pin_array_size_t = decltype(this->data_pins)::size_type;

  std::bitset<data_bus_width> data_bits;
  for (pin_array_size_t i{0}; i < this->data_pins.size(); ++i) {
    data_bits[i] = digitalRead(this->data_pins[i]);
  }
  return data_bits.to_ulong();
}
