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

    // prepare averaging buffer
    for (int i=0; i<COMPASS_AVERAGE_BUFFER; i++) {
        _compass.average[i] = 0;
    }
}


void compass_loop()
{
    
    // don't read compass while motor is running, because of possible magnetic interference
    if (motor.running) return;

    // set "inited" flag
    compass.inited = true;

    // read sensor data and calculate raw value

    // get a new sensor data
    _compass.sensor.read();

    _compass.B = sqrt(
        pow(_compass.sensor.magData.x, 2.0) + 
        pow(_compass.sensor.magData.y, 2.0) +
        pow(_compass.sensor.magData.z, 2.0)
    );
    _compass.phi = atan2(
        -1 * _compass.sensor.accelData.y,
        _compass.sensor.accelData.z
    );
    _compass.theta = atan(
        -1 * _compass.sensor.accelData.x /
        (_compass.sensor.accelData.y * sin(_compass.phi) - _compass.sensor.accelData.z * cos(_compass.phi))
    );
    _compass.delta = asin(
        _compass.sensor.magData.x / _compass.B * sin(_compass.theta) -
        _compass.sensor.magData.y / _compass.B * cos(_compass.theta) * sin(_compass.phi) +
        _compass.sensor.magData.z / _compass.B * cos(_compass.theta) * cos(_compass.phi)
    );
    _compass.Dx = (
        _compass.sensor.magData.x * cos(_compass.theta) + 
        _compass.sensor.magData.y * sin(_compass.theta) * sin(_compass.phi) - 
        _compass.sensor.magData.z * sin(_compass.theta) * cos(_compass.phi)
    ) / (
        _compass.B * cos(_compass.delta)
    );
    _compass.Dy = (
        _compass.sensor.magData.y * cos(_compass.phi) +
        _compass.sensor.magData.z * sin(_compass.phi)
    ) / (
        _compass.B * cos(_compass.delta)
    );
    _compass.psi = asin(
        _compass.Dy * cos(_compass.alpha) - _compass.Dx * sin(_compass.alpha)
    );

    if (_compass.Dx < 0) {
        _compass.psi = M_PI - _compass.psi;
    }

    /***** Put it into average buffer *****/
    _compass.average_i++;
    _compass.average_i = _compass.average_i % COMPASS_AVERAGE_BUFFER;
    _compass.average[_compass.average_i] = _compass.psi;

    /***** Calculate azimuth *****/
    compass.azimuth = 0;
    for (int i=0; i<COMPASS_AVERAGE_BUFFER; i++) {
        compass.azimuth += _compass.average[i] / COMPASS_AVERAGE_BUFFER;
    }
}
