

/*
 * Available choices for HARDWARE preprocessor variable:
 *
 * "micro"
 * - Arduino ProMini
 *
 * "mega"
 * - Arduino Mega
 */

#ifndef HARDWARE_CONFIG_H
#define HARDWARE_CONFIG_H


// common:

#define SERIAL_BAUD_RATE 9600


// hardware-specific:

#if HARDWARE == HARDWARE_1284

  // blink
  #define BLINK_LED_PIN 0
  // #define ENCODER_PINS {0, 1, 2, 3, 4, 5, 6, 7}
  #define ENCODER_PINS {7, 6, 5, 4, A7, A6, A5, A4}
  // RAM_USAGE:
  #define RAM_TOTAL (1024 * 16)

  // EEPROM addresses:
  #define ACC_CALIBRATION_EEPROM_ADDR_BASE 200
  #define MAG_CALIBRATION_EEPROM_ADDR_BASE 300

  #define ARROW_EEPROM_BASE_ADDR 400
  #define DECLINATION_EEPROM_ADDR 500

  #define TARGET_EEPROM_ADDR_BASE 800  // 20

#else  // #if HARDWARE == HARDWARE_<something>

  // throw compiler error:
  #ifndef HARDWARE
    #error Define HARDWARE preprocessor var. See hardware_options.h for possible choices.
  #else
    #error Unknown value in HARDWARE. See hardware_options.h for possible choices.
  #endif

#endif  // #if HARDWARE == HARDWARE_<something>

#endif  // #ifndef HARDWARE_CONFIG_H
