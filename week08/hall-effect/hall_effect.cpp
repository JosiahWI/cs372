#include "hall_effect.h"

#include <Wire.h>

#include <array>
#include <cassert>
#include <functional>
#include <string>

namespace {
constexpr int chip_id_rev{0x14};
constexpr int reg_chip_info{0xc0};
constexpr int reg_dspsigm{0xc1};
constexpr int reg_dspsigl{0xc2};
constexpr int reg_settings{0xc4};
constexpr std::array<int, 4> valid_chip_addresses{0x30, 0x31, 0x32, 0x33};
} // end anonymous namespace

HallEffect::HallEffect()
{
  Wire1.begin();
  if (!this->verify_slave_device()) {
    this->failed = true;
  }
}

HallEffect::~HallEffect()
{
  Wire1.end();
}

bool
HallEffect::verify_slave_device()
{
  // The chip can have one of four addresses, hardcoded at the factory. We
  // have to try all four to determine which address it actually has.
  for (int addr : valid_chip_addresses) {
    this->address = addr;
    this->request_register(reg_chip_info);
    if (this->is_failed()) {
      break;
    }
    if (chip_id_rev == this->get_byte_blocking()) {
      this->address = addr;
      return true;
    }
  }
  return false;
}

bool
HallEffect::is_failed() const
{
  return this->failed;
}

void
HallEffect::request_register(int reg)
{
  Wire1.beginTransmission(this->address);
  Wire1.write(reg);
  int status{Wire1.endTransmission()};
  switch (status) {
    case 0:
      Wire1.requestFrom(this->address, 1);
      return;
    case 2:
      return;
    default:
      this->failed = false;
      return;
  }
}

int
HallEffect::get_byte_blocking()
{
  while (Wire1.available() == 0) {}
  return Wire1.read();
}

void
HallEffect::start_reading()
{
  if (this->is_failed() || this->transfer_in_progress) {
    return;
  }

  this->transfer_in_progress = true;

  this->set_oneburst();
  this->set_handler(&HallEffect::fetch_high_byte);
}

bool
HallEffect::has_fresh_value() const
{
  return this->value_fresh;
}

int
HallEffect::get_value() const
{
  this->value_fresh = false;
  return this->last_value;
}

void
HallEffect::set_oneburst()
{
  Wire1.beginTransmission(this->address);
  Wire1.write(reg_settings);
  Wire1.write(0x4);
  Wire1.endTransmission();
}

void
HallEffect::fetch_high_byte()
{
  this->request_register(reg_dspsigm);
  this->set_handler(&HallEffect::read_high_byte);
}

void
HallEffect::fetch_low_byte()
{
  this->request_register(reg_dspsigl);
  this->set_handler(&HallEffect::read_low_byte);
}

void
HallEffect::read_high_byte()
{
  if (Wire1.available() > 0) {
    this->high_reg_byte = Wire1.read();
    this->set_handler(&HallEffect::fetch_low_byte);
  }
}

void
HallEffect::read_low_byte()
{
  if (Wire1.available() > 0) {
    this->high_reg_byte = Wire1.read();
    this->clear_handler();
    this->recalc_value();
    this->transfer_in_progress = false;
  }
}

void
HallEffect::recalc_value()
{
  unsigned int full_value{((this->high_reg_byte & 0x7f) << 8) | this->low_reg_byte};
  this->last_value = (static_cast<int>(full_value) - 16384) / 800;
  this->value_fresh = true;
}
