/**
 * Power function for integers
 * For floats, use built-in pow()
 */
int power(int base, int exponent)
{
	return (int) (0.5 + pow(base, exponent));
}


/*
 * Make sure argument is within [0, 360) range
 */
double map_to_circle(double azimuth)
{
    while(azimuth < 0.0) {
        azimuth += 360.0;
    }
    while(azimuth >= 360.0) {
        azimuth -= 360.0;
    }
    return azimuth;
}

double map_to_circle_rad(double azimuth)
{
    while(azimuth < 0.0) {
        azimuth += 2 * M_PI;
    }
    while(azimuth >= M_PI) {
        azimuth -= 2 * M_PI;
    }
    return azimuth;
}



double deg2rad(double deg)
{
	return deg / 180.0 * M_PI;
}

double rad2deg(double rad)
{
	return rad / M_PI * 180.0;
}
