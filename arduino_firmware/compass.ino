#include "compass.h"

void compass_setup()
{
	;
}

void compass_loop()
{
	// mock values:
	if (! compass.inited) {
		compass.inited = true;
		compass.azimuth = 25.0;
	}
}
