#include "gps.h"

void gps_setup()
{
	;
}


void gps_loop()
{
	// mockup:
	if (! gps.inited) {
		gps.inited = true;
		gps.current_lat = deg2rad(44.0);
		gps.current_lon = deg2rad(9.0);
		gps.target_lat = deg2rad(45.0);
		gps.target_lon = deg2rad(9.0);
	}

	// calculate azimuth and distance
	if (gps.inited) {
		gps.azimuth = map_to_circle_rad(M_PI / 2 - atan2(
			gps.target_lat - gps.current_lat,
			gps.target_lon - gps.current_lon
		));

		// Flat Earth approximation (we only ever use distance for determining if on-target)
		gps.distance = sqrt(
			pow((gps.target_lat - gps.current_lat) * _gps.earth_cr /  2 / M_PI, 2) 
			+
			pow((gps.target_lon - gps.current_lon) * _gps.earth_cr /  2 / M_PI * cos(gps.current_lat), 2)
		);

		// is target reached:
		gps.on_target = gps.distance < gps.target_zone;
	}
}
