#include <Arduino.h>
#include "modules.hpp"

#include "_blink.hpp"


// Unlike header file (.hpp), module implementation file (.ino.h) must not be included multiple times:
#ifdef BLINK_INO_HPP
#error The .ino.hpp file of a module can be included only once (and should be included from main.ino). Did you wanted to include the .hpp file instead?
#endif
#define BLINK_INO_HPP


#ifndef BLINK_LED_PIN
  #define BLINK_LED_PIN 13
#endif


void Blink::setup()
{
  pinMode(BLINK_LED_PIN, OUTPUT);
  _pattern_i = 0;
  pattern_i = 0;
  last_blink = 0;
  // initial pattern:
  set_pattern = BLINK_PATTERN_SETUP_I;
}


void Blink::loop()
{
  // check pattern setter:
  if (set_pattern != -1) {
    // make sure pattern pointer is valid:
    if (set_pattern >= BLINK_PATTERNS_N) {
      Serial.println(F("Blink: Invalid pattern!"));
    }
    // load new pattern:
    pattern = & patterns[set_pattern * BLINK_INTERVALS_N];
    // start new pattern from the beginning:
    _pattern_i = 0;
    // start it now:
    last_blink = 0;
    // clear the setter:
    set_pattern = -1;
  }

  // actually blink, according to pattern:
  if (millis() - last_blink > pattern[_pattern_i]) {  // TODO make millis overflow-safe
    last_blink = millis();
    _pattern_i++;
    if (_pattern_i >= BLINK_INTERVALS_N) _pattern_i = 0;
    digitalWrite(BLINK_LED_PIN, _pattern_i % 2 == 0);
  }
  //digitalWrite(BLINK_LED_PIN, ! digitalRead(BLINK_LED_PIN));

  // set public pattern_i property:
  pattern_i = _pattern_i;
 digitalWrite(BLINK_LED_PIN, HIGH);


  #ifdef RAM_USAGE_H
  ram->measure(1);
  #endif
}
