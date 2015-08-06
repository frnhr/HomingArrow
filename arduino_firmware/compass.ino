#include "compass.h"

void compass_setup()
{
	;
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
	// TODO https://github.com/adafruit/Adafruit_HMC5883_Unified/blob/master/examples/magsensor/magsensor.ino
	// _compass.last_value = _encoder.GRAY2BIN[_encoder.gray_code];

	// set offset if commanded
	if (compass.set_north) {
		compass.set_north = false;
		_compass.offset = _compass.last_value + compass.magnetic_declination;
	}

	/***** Calculate azimuth *****/
	compass.azimuth = map_to_circle_rad(_compass.last_value - _compass.offset + compass.magnetic_declination);
}
