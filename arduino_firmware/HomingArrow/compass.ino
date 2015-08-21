#include "compass.h"


void compass_setup()
{
	/* Initialise the sensor */
	if(!_compass.sensor.begin()) {
		/* There was a problem detecting the HMC5883 ... check your connections */
		Serial.println(F("Ooops, no HMC5883 detected ... Check your wiring!"));
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

	/* Get a new sensor event */
	_compass.sensor.getEvent(&_compass.event);
    _compass.last_value = map_to_circle_rad(atan2(_compass.event.magnetic.y, _compass.event.magnetic.x));
  

	// set offset if commanded
	if (compass.set_north) {
		compass.set_north = false;
		_compass.offset = _compass.last_value + COMPASS_MAGNETIC_DECLINATION;
	}

	/***** Calculate azimuth *****/
	compass.azimuth = map_to_circle_rad(_compass.last_value - _compass.offset + COMPASS_MAGNETIC_DECLINATION);
}
