#include "status.h"

void status_loop()
{
	// all devices need to be ready (initialised)
	if (! encoder.inited) return;
  #ifdef COMPASS_HPP
	if (! compass.inited) return;
  #endif
	if (! gps.inited) return;

	if (! status.inited) status.inited = true;

	// calculate arrow azimuth based on compass na dencoder azimuths
	status.azimuth = map_to_circle_rad(encoder.azimuth + compass.azimuth);
	status.azimuth_delta = map_to_half_circle_rad(gps.azimuth - status.azimuth);
}
