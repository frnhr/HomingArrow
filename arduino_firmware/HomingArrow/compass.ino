#include "compass.h"


void compass_setup()
{
    /* Initialise the sensor */
    if(!_compass.sensor.begin()) {
        /* There was a problem detecting the HMC5883 ... check your connections */
        Serial.print(F("Ooops, no LS303 detected ... Check your wiring!\n"));
        delay(500);
        while(1);
    }
}


void compass_loop()
{
    
    // don't read compass while motor is running, because of magnetic interference
    //if (motor.running) return;

    // set "inited" flag
    if (! compass.inited) compass.inited = true;

    // read sensor data and calculate raw value

    // get a new sensor data
    _compass.sensor.read();

    // compensate sensor tilt with accelerometer
    _compass.alpha_x = asin(min(1.0, max(-1.0, _compass.sensor.accelData.x / COMPASS_MAX_ACCEL)));
    _compass.alpha_y = asin(min(1.0, max(-1.0, _compass.sensor.accelData.y / COMPASS_MAX_ACCEL)));
    _compass.corrected_x = _compass.sensor.magData.x / cos(_compass.alpha_x);
    _compass.corrected_y = _compass.sensor.magData.y / cos(_compass.alpha_y);

    // calculate raw heading 
    _compass.last_value = map_to_circle_rad(
        atan2(_compass.corrected_y, _compass.corrected_x)
    );
  
    /***** Calculate azimuth *****/
    compass.azimuth = map_to_circle_rad(_compass.last_value + COMPASS_MAGNETIC_DECLINATION);
}

