
#include "battery.h"

void battery_setup() 
{
	;  // nothing to do...
}


/**
 * Keep this loop at less then 10 kHz, because ADC needs 0.1 millis to sample input.
 */
void battery_loop()
{
	battery.voltage = ((float) analogRead(BATTERY_ADC_PIN)) / 1024.0 * 5.0 * BATTERY_DIVIDER;
	battery.is_low = battery.voltage < BATTERY_TRESHOLD;
}
