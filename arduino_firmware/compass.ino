#include "compass.h"


void compass_setup()
{
	/* Initialise the sensor */
	if(!_compass.sensor.begin()) {
		/* There was a problem detecting the HMC5883 ... check your connections */
		Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
		while(1);
	}
}

void compass_loop()
{
	// mock values:
	if (! compass.inited) {
		_compass.last_value = map_to_circle_rad(atan2(10, 10));
	};


	/***** normal operation *****/

	// set "inited" flag
	if (! compass.inited) compass.inited = true;
	
	// read sensor data and calculate raw value

	/* Get a new sensor event */ 
	sensors_event_t event; 
	_compass.sensor.getEvent(&event);
    _compass.last_value = map_to_circle_rad(atan2(event.magnetic.y, event.magnetic.x));
  
	// _compass.last_value = _encoder.GRAY2BIN[_encoder.gray_code];

	// set offset if commanded
	if (compass.set_north) {
		compass.set_north = false;
		_compass.offset = _compass.last_value + compass.magnetic_declination;
	}

	/***** Calculate azimuth *****/
	compass.azimuth = map_to_circle_rad(_compass.last_value - _compass.offset + compass.magnetic_declination);
}
