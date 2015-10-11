#include "Calibration.h"
#include "serial.h"
#include "compass.h"


void setup()
{
    delay(1000);  // prevent double welcome message
    serial_setup();
    compass_setup();
}


void loop()
{
    realtime_loop();

    if (compass.just_updated) {
        _loop.slow_timer = 0;
    }

    _loop.now = millis();
    if (_loop.now - _loop.fast_timer >= LOOP_FAST_INTERVAL) {
        _loop.fast_timer = _loop.now;
        fast_loop();
    }
    if (_loop.now - _loop.slow_timer >= LOOP_SLOW_INTERVAL) {
        _loop.slow_timer = _loop.now;
        slow_loop();
    }
}


/**
 * Runs as fast as possible
 */
void realtime_loop()
{
    compass_loop();
}


/**
 * Runs frequently, as defined in _loop.fast_interval
 */
void fast_loop()
{
    serial_loop();
}


/**
 * Runs not-so-frequently, as defined in _loop.slow_interval
 */
void slow_loop()
{
    compass_serial_loop();
}
