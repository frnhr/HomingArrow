#include "HomingArrow.h"


void setup()
{
    delay(2000);  // prevent double welcome message
    battery_setup();
    serial_setup();
    compass_setup();
    gps_setup();
    encoder_setup();
    motor_setup();
    blink_setup();
}


void loop()
{
    realtime_loop();

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
    serial_loop();
    encoder_loop();
    status_loop();
    motor_loop();
    blink_loop();
}


/**
 * Runs frequently, as defined in _loop.fast_interval
 */
void fast_loop()
{
    battery_loop();
    compass_loop();
}


/**
 * Runs not-so-frequently, as defined in _loop.slow_interval
 */
void slow_loop()
{
    gps_loop();
}
