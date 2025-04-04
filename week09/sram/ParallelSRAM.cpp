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

  for (int data_pin : this->data_pins) {
    pinMode(data_pin, INPUT);
  }

  for (int addr_pin : this->addr_pins) {
    pinMode(addr_pin, OUTPUT);
  }

  pinMode(this->write_enable_pin, OUTPUT);
  pinMode(this->output_enable_pin, OUTPUT);

  this->enable_highz();
}

ParallelSRAM::~ParallelSRAM()
{
}

byte
ParallelSRAM::readSRAM(byte addr)
{
  this->enable_highz();
  this->write_addr(addr);
  this->enable_read();
  return static_cast<byte>(this->read_ulong());
}

void
ParallelSRAM::writeSRAM(byte addr, byte data)
{
  this->enable_highz();
  this->write_addr(addr);
  this->do_write(data);
}

void
ParallelSRAM::enable_highz()
{
  digitalWrite(this->output_enable_pin, HIGH);
  digitalWrite(this->write_enable_pin, HIGH);
#ifdef SAFETY_CHECK_HIGH_Z
  this->is_high_z = true;
#endif
}

void
ParallelSRAM::enable_read()
{
#ifdef SAFETY_CHECK_HIGH_Z
  if (!this->is_high_z) {
    return;
  }
#endif

  this->is_high_z = false;

  for (int data_pin : this->data_pins) {
    pinMode(data_pin, INPUT);
  }
  digitalWrite(this->output_enable_pin, LOW);
}

void
ParallelSRAM::do_write(byte data)
{
#ifdef SAFETY_CHECK_HIGH_Z
  if (!this->is_high_z) {
    return;
  }
  this->is_high_z = false;
#endif

  using pin_array_size_t = decltype(this->data_pins)::size_type;

  std::bitset<data_bus_width> data_bits{data};
  for (pin_array_size_t i{0}; i < this->data_pins.size(); ++i) {
    pinMode(this->data_pins[i], OUTPUT);
    digitalWrite(this->data_pins[i], data_bits[i]);
  }
  // Write must be enabled only after value has been set on data bus.
  digitalWrite(this->write_enable_pin, LOW);
}

void
ParallelSRAM::write_addr(byte addr)
{
#ifdef SAFETY_CHECK_HIGH_Z
  if (!this->is_high_z) {
    return;
  }
#endif

  using pin_array_size_t = decltype(this->addr_pins)::size_type;

  std::bitset<addr_bus_width> addr_bits{addr};
  for (pin_array_size_t i{0}; i < this->addr_pins.size(); ++i) {
    digitalWrite(this->addr_pins[i], addr_bits[i]);
  }
}

unsigned long
ParallelSRAM::read_ulong()
{
#ifdef SAFETY_CHECK_HIGH_Z
  if (!this->is_high_z) {
    return -1;
  }
#endif

  using pin_array_size_t = decltype(this->data_pins)::size_type;

  std::bitset<data_bus_width> data_bits;
  for (pin_array_size_t i{0}; i < this->data_pins.size(); ++i) {
    data_bits[i] = digitalRead(this->data_pins[i]);
  }
  return data_bits.to_ulong();
}
