/** Ram usage module
 *
 */

// Start every module with at least these two includes:
#include <Arduino.h>
#include "modules.hpp"

#ifndef RAM_USAGE_HPP
#define RAM_USAGE_HPP



// Optionally enable RAM usage measurements:
#ifndef RAM_MEASUREMENTS_N
#define RAM_MEASUREMENTS_N MODULE_MAX_N  // default value for MODULE_MAX_N
#endif

#ifndef RAM_TOTAL
#define RAM_TOTAL 2048
#endif


// Module:
class Ram: public Module
{
public:
  uint16_t step = 5000;  // run on every "step-th" loop
  uint16_t step_i = 0;
  int32_t measurements[RAM_MEASUREMENTS_N];
  void measure(uint8_t index);
  void measure_now(uint8_t index);
  void print_mesaurements();
  void setup();
  void loop();
};


// Instantiate the module class:
Ram* ram = (Ram*) ModulesRegistry::add(new Ram());


#endif  // #ifndef RAM_USAGE_HPP
