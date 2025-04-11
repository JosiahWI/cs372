#include "cs372ecc.h"

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <cstdint>

TEST_CASE("Even parity.")
{
  SECTION("When we generate parity for all zeroes, "
          "then we should get parity bit 0.")
  {
    CHECK(gen_parity(0x0) == 0);
  }

  SECTION("When we generate parity for a byte with odd number of ones, "
          "then we should get parity bit 1.")
  {
    CHECK(gen_parity(0x1) == 1);
    CHECK(gen_parity(0x7) == 1);
  }

  SECTION("When we generate parity for a byte with even number of ones, "
          "then we should get parity bit 0.")
  {
    CHECK(gen_parity(0x3) == 0);
    CHECK(gen_parity(0x5) == 0);
  }

  SECTION("When we check parity and it is correct, "
          "then we should get a 1 back.")
  {
    CHECK(check_parity(0x0, 0) == 1);
    CHECK(check_parity(0x5, 0) == 1);
    CHECK(check_parity(0x7, 1) == 1);
  }

  SECTION("When we check parity and it is incorrect, "
          "then we should get a 0 back.")
  {
    CHECK(check_parity(0x0, 1) == 0);
    CHECK(check_parity(0x5, 1) == 0);
    CHECK(check_parity(0x7, 0) == 0);
  }
}

TEST_CASE("Hamming(12,8) codes (even parity).")
{
  SECTION("When we generate hamming for all zeroes, "
          "then parity bits should all be 0 as well.")
  {
    CHECK(gen_hamming(0x00) == 0x0000);
  }

  SECTION("When we generate hamming, "
          "then the data bits should be correct.")
  {
    CHECK((gen_hamming(0xff) & 0x02ef) == 0x02ef);
    CHECK((gen_hamming(0xaa) & 0x02ef) == 0x024a);
    CHECK((gen_hamming(0x55) & 0x02ef) == 0x00a5);
  }

  SECTION("When we generate hamming, "
          "then the first parity bit should be correct.")
  {
    CHECK((gen_hamming(0xda) & 0x0800) == 0x0800);
    CHECK((gen_hamming(0x9a) & 0x0800) == 0x0000);
  }

  SECTION("When we generate hamming, "
          "then the second parity bit should be correct.")
  {
    CHECK((gen_hamming(0xb6) & 0x0400) == 0x0400);
    CHECK((gen_hamming(0x96) & 0x0400) == 0x0000);
  }

  SECTION("When we generate hamming, "
          "then the third parity bit should be correct.")
  {
    CHECK((gen_hamming(0x71) & 0x0100) == 0x0000);
    CHECK((gen_hamming(0x61) & 0x0100) == 0x0100);
    CHECK((gen_hamming(0x70) & 0x0100) == 0x0100);
  }

  SECTION("When we generate hamming, "
          "then the fourth parity bit should be correct.")
  {
    CHECK((gen_hamming(0x0f) & 0x0010) == 0x0000);
    CHECK((gen_hamming(0x0d) & 0x0010) == 0x0010);
    CHECK((gen_hamming(0x0b) & 0x0010) == 0x0010);
  }

  SECTION("When we check uncorrupted hamming encoded data, "
          "then we should get the same value back.")
  {
    std::uint16_t data{gen_hamming(0xbe)};
    CHECK(check_hamming(data) == data);
  }

  SECTION("When we check data with a corrupted parity bit, "
          "then that parity bit should be fixed.")
  {
    std::uint16_t data{gen_hamming(0xbe)};
    CHECK(check_hamming(data | 0x0800) == data);
    CHECK(check_hamming(data & 0xfbff) == data);
    CHECK(check_hamming(data | 0x0100) == data);
    CHECK(check_hamming(data & 0xffef) == data);
  }

  SECTION("When we check data with a corrupted data bit, "
          "then that data bit should be fixed.")
  {
    std::uint16_t data{gen_hamming(0x26)};
    CHECK(check_hamming(data & 0xffbf) == data);
    CHECK(check_hamming(data | 0x0200) == data);
  }
}
