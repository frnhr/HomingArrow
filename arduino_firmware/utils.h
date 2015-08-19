#ifndef _INCL_HOMING_ARROW_UTILS
#define _INCL_HOMING_ARROW_UTILS

#include <math.h>

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
    while (azimuth < 0.0) {
        azimuth += 360.0;
    }
    while (azimuth >= 360.0) {
        azimuth -= 360.0;
    }
    return azimuth;
}

double map_to_circle_rad(double azimuth)
{
    while (azimuth < 0.0) {
        azimuth += 2 * M_PI;
    }
    while (azimuth >= 2 * M_PI) {
        azimuth -= 2 * M_PI;
    }
    return azimuth;
}

double map_to_half_circle_rad(double azimuth)
{
    while (azimuth <= M_PI) {
        azimuth += 2 * M_PI;
    }
    while (azimuth > M_PI) {
        azimuth -= 2 * M_PI;
    }
    return azimuth;
}


double closer_route(double azimuth, double target_azimuth)
{    
    double distance = map_to_circle_rad(target_azimuth - azimuth);
    double delta;
    
    if (distance < M_PI) {
        delta = distance;
    } else {
        delta = abs(distance - 2 * M_PI);
    }
    return delta;
}


double deg2rad(double deg)
{
	return deg * M_PI / 180.0 ;
}

double rad2deg(double rad)
{
	return rad * 180.0 / M_PI ;
}


/**
 * Get part of char-separated string
 */
String partialString(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = {0, -1};
    int maxIndex = data.length()-1;
    for (int i=0; i<=maxIndex && found<=index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i + 1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

#endif
