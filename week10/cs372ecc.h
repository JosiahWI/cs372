#ifndef CS372_ECC_H_INCLUDED
#define CS372_ECC_H_INCLUDED

#include <cstdint>

std::uint8_t gen_parity(std::uint8_t _byte);

std::uint8_t check_parity(std::uint8_t _byte, std::uint8_t parity);

std::uint16_t gen_hamming(std::uint8_t _byte);

std::uint16_t check_hamming(std::uint16_t word);

#endif // CS372_ECC_H_INCLUDED
