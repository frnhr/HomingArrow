#ifndef _INCL_HOMING_ARROW_GPS
#define _INCL_HOMING_ARROW_GPS

/***** DEPENDENCIES *****/

#include "utils.h"
#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>


/***** CONFIGURATION *****/

#define GPS_PIN_RX A1
#define GPS_PIN_TX A0
#define GPS_BAUD_RATE 9600
#define GPS_EARTH_CIRCUMFERRENCE 6371009 * 2 * M_PI
#define GPS_ECHO false

/***** MODULE *****/

// provides: gps

// reads: --
// writes: --


/***** INTERFACE *****/

typedef struct {
    double current_lon;    // cirrent position, distance from the Prime Meridian, negative for W
    double current_lat;    // current positon, distance from the Equator, negative for S
    double target_lon;     // target longitude
    double target_lat;     // target latitude
    double azimuth;        // azimuth to target
    double distance;       // target distance
    double target_zone;    // radius around target coords that is considered to be "on target"
    bool on_target;        // target reached
    bool inited;           // device is ready
} GPSInterface;
GPSInterface gps = {
    0.0,        // current_lon
    0.0,        // current_lat
    0.0,        // target_lon
    0.0,        // target_lat
    0.0,        // distance
    0.0,        // azimuth
    10.0,       // target_zone
    false,      // on_target
    false       // inited
};


/***** INTERNALS *****/

SoftwareSerial gpsSerial(GPS_PIN_RX, GPS_PIN_TX);

typedef struct {
    Adafruit_GPS sensor;
    String buffer;
} GPSInternals;
GPSInternals _gps = {
    Adafruit_GPS(&gpsSerial),  // sensor
    "",                        // buffer
};


/* PROTOTYPES */

void gps_setup();
void gps_loop();

#endif
