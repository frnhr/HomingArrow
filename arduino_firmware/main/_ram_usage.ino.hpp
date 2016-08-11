/*
   Implementation of RamUsage module

*/

// Start every module with at least these two includes:
#include <Arduino.h>
#include "modules.hpp"
// Also include this module's header file:
#include "_ram_usage.hpp"

// Unlike header file (.h), module implementation file (.ino.h) must not be included multiple times:
#ifdef RAM_USAGE_INO_HPP
#error The .ino.h file of a module can be included only once (and should be included from main.ino). Did you wanted to include the .h file instead?
#endif
#define RAM_USAGE_INO_HPP


void Ram::setup()
{
  for (step_i=0; step_i<RAM_MEASUREMENTS_N; step_i++) {
    measurements[step_i] = -1;
  }
  step_i = 0;
}


void Ram::loop()
{
  step_i++;

  ram->measure(0);
  if (step_i % step == 0) {
    ram->print_mesaurements();
    step_i = 0;
  }
}


void Ram::measure(uint8_t index) {
  if (step_i % step != 0) return;

  extern int __heap_start, *__brkval;
  int v;
  Ram::measurements[index] = (int32_t) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
};


void Ram::measure_now(uint8_t index) {
  extern int __heap_start, *__brkval;
  int v;
  Ram::measurements[index] = (int32_t) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
};


void Ram::print_mesaurements() {
  extern int __heap_start, *__brkval;
  int v, r;
  uint8_t i=0;
  Serial.print(F("\nRAM:\n"));
  for (i=0; i<RAM_MEASUREMENTS_N; i++) {
    Serial.print(i);
    Serial.print(F(" : "));
    if (Ram::measurements[i] > -1) {
      Serial.print(RAM_TOTAL - Ram::measurements[i]);
      Serial.flush();
      Serial.print(F(" + "));
      Serial.flush();
      Serial.print(Ram::measurements[i]);
      Serial.flush();
      Ram::measurements[i] = -1;
    }
    Serial.print(F("\n"));
    Serial.flush();
  }

  r = (int32_t) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
  Serial.println(r);
  Serial.flush();

  Serial.print(F("\n"));
  Serial.flush();
};
