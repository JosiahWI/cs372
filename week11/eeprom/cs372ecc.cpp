#include "cs372ecc.h"

#include <bitset>
#include <type_traits>

/* This function is provided by the C++20 standard library, but it seems
 * Arduino does not have it.
 */
template <typename T>
std::uint8_t
popcount(T data)
{
  return std::bitset<8 * sizeof(T)>{data}.count();
}

template <typename T>
std::uint8_t
gen_parity_impl(T data)
{
  return popcount(static_cast<std::make_unsigned_t<T>>(data)) % 2;
}

template <typename T>
std::uint8_t
check_parity_impl(T data, std::uint8_t parity)
{
  return gen_parity_impl(data) == parity;
}

std::uint8_t
gen_parity(std::uint8_t _byte)
{
  return gen_parity_impl<std::uint8_t>(_byte);
}

std::uint8_t
check_parity(std::uint8_t _byte, std::uint8_t parity)
{
  return check_parity_impl(_byte, parity);
}

std::uint16_t
gen_hamming(std::uint8_t _byte)
{
  std::uint16_t result{0};
  result |= (_byte & 0x80) << 2;
  result |= (_byte & 0x70) << 1;
  result |= (_byte & 0x0f);
  result |= gen_parity(_byte & 0xda) << 11;
  result |= gen_parity(_byte & 0xb6) << 10;
  result |= gen_parity(_byte & 0x71) << 8;
  result |= gen_parity(_byte & 0x0f) << 4;
  return result;
}

std::uint16_t
check_hamming(std::uint16_t word)
{
  std::bitset<16> data{word};
  unsigned int    error_loc{0};
  if (!check_parity_impl(word & 0x02aa, (word & 0x0800) > 0)) {
    error_loc |= 1;
  }
  if (!check_parity_impl(word & 0x0266, (word & 0x0400) > 0)) {
    error_loc |= 2;
  }
  if (!check_parity_impl(word & 0x00e1, (word & 0x0100) > 0)) {
    error_loc |= 4;
  }
  if (!check_parity_impl(word & 0x000f, (word & 0x0010) > 0)) {
    error_loc |= 8;
  }
  if (error_loc != 0) {
    data.flip(12 - error_loc);
  }
  return data.to_ulong();
}
