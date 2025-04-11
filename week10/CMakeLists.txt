cmake_minimum_required(VERSION 3.31)

project(libecc
  DESCRIPTION "Error correction library for Teensy"
  VERSION 0.1.0
  LANGUAGES CXX
)

add_library(ecc cs372ecc.cpp)
add_library(ecc::ecc ALIAS ecc)

target_compile_features(ecc PRIVATE cxx_std_20)
target_compile_options(ecc PRIVATE -Wall -Wextra -Wshadow)

find_package(Catch2 REQUIRED)

add_executable(test_ecc test_ecc.cpp)
target_link_libraries(test_ecc PRIVATE Catch2::Catch2 ecc::ecc)

add_custom_target(
  format clang-format -i *.cpp *.h
  WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
)
