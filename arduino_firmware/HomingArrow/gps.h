#ifndef _INCL_HOMING_ARROW_GPS
#define _INCL_HOMING_ARROW_GPS

/***** DEPENDENCIES *****/

#include "utils.h"
#include <EEPROM.h>
#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>


/***** CONFIGURATION *****/

#define GPS_PIN_RX A1
#define GPS_PIN_TX A0
#define GPS_BAUD_RATE 9600
#define GPS_EARTH_CIRCUMFERRENCE 6371009 * 2 * M_PI
#define GPS_ECHO false

#define GPS_EEPROM_ADDR 10
#define GPS_EEPROM_ADDR_LAT GPS_EEPROM_ADDR + 0
#define GPS_EEPROM_ADDR_LON GPS_EEPROM_ADDR + 4
#define GPS_EEPROM_ADDR_ZONE GPS_EEPROM_ADDR + 8

/***** MODULE *****/

/**
    This module handles all GPS-related functions. This includes:
     - reading GPS module for current coordinates
     - storing target coordinates
     - calculating distance and geographical azimuth between current and target locations

    For a quick way to get GPS coordaintes from a map, see
    http://itouchmap.com/latlong.html 
*/  

// provides: gps

// reads: --
// writes: --


/***** INTERFACE *****/

struct {
    double current_lat = 0.0;      // current positon, distance from the Equator, negative for S
    double current_lon = 0.0;      // cirrent position, distance from the Prime Meridian, negative for W
    double target_lat = 90.0;      // target latitude
    double target_lon = 0.0;       // target longitude
    double set_target_lat = 90.0;  // target latitude, degrees
    double set_target_lon = 0.0;   // target longitude, degrees
    double azimuth = 0.0;          // azimuth to target
    double distance = 0.0;         // target distance
    double target_zone = 10.0;     // radius around target coords that is considered to be "on target"
    bool on_target = false;        // target reached
    bool inited = false;           // device is ready
    bool fix = false;              // GPS receiver has a sattelite fix
} gps;


/***** INTERNALS *****/

SoftwareSerial gpsSerial(GPS_PIN_RX, GPS_PIN_TX);

struct {
    Adafruit_GPS sensor = Adafruit_GPS(&gpsSerial);   // library object
    String buffer = "";
    double last_target_lat = 0.0;
    double last_target_lon = 0.0;
    double target_zone = 0.0;
} _gps;


/* PROTOTYPES */

void gps_setup();
void gps_loop();

#endif
