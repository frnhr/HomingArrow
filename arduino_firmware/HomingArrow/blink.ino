
#include "blink.h"

void blink_setup() 
{
    pinMode(BLINK_LED, OUTPUT);
    blink.pattern = _blink.pattern_setup;
}


void blink_loop()
{

    /*** Select blink pattern ***/

    if (_blink.i == 0) {  // only if at the start of a pattern
        if (battery.is_low) {
            blink.pattern = _blink.pattern_battery;
        } else {
            if (status.inited) {
                if (! gps.fix) {
                    blink.pattern = _blink.pattern_gps;
                } else {
                    blink.pattern = _blink.pattern_idle;
                }
            } else {
                blink.pattern = _blink.pattern_setup;
            }
        }
    }

    

    /*** Do the blinking ***/

    if (millis() - _blink.last_blink > blink.pattern[_blink.i]) {  // TODO make overflow-safe
        _blink.last_blink = millis();
        _blink.i++;
        if (_blink.i >= BLINK_INTERVALS_N) _blink.i = 0;

        digitalWrite(BLINK_LED, _blink.i % 2 == 0);
    }
}
