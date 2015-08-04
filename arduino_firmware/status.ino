#include "status.h"

void status_loop()
{
	// all devices need to be ready (initialised)
	if (! encoder.inited) return;
	if (! compass.inited) return;
	if (! gps.inited) return;

	// calculate azimuths


}
