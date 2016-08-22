/**
    This module handles all GPS-related functions. This includes:
     - reading GPS module for current coordinates
     - storing target coordinates
     - calculating distance and geographical azimuth between current and target locations

    For a quick way to get GPS coordaintes from a map, see
    http://itouchmap.com/latlong.html
*/

#include <Arduino.h>
#include "modules.hpp"


#ifndef SENSOR_GPS_HPP
#define SENSOR_GPS_HPP


#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>


#define SENSOR_GPS_PIN_RX A1
#define SENSOR_GPS_PIN_TX A0
#define SENSOR_GPS_BAUD_RATE 9600
#define SENSOR_GPS_ECHO false

#define SENSOR_GPS_NULL_VALUE 500.0
#define SENSOR_GPS_NULL_EPSILON 0.1


class SensorGps: public Module
{
private:
  String _buffer = "";

public:
  Adafruit_GPS* _sensor;   // library object
  bool inited = false;     // device is ready
  bool fix = false;        // got GPS signal fix
  void setup();
  void loop();
  SensorGps() {
    SoftwareSerial* gpsSerial = new SoftwareSerial(SENSOR_GPS_PIN_RX, SENSOR_GPS_PIN_TX);
    _sensor = new Adafruit_GPS(gpsSerial);
  }
};

SensorGps* sensor_gps = (SensorGps*) ModulesRegistry::add(new SensorGps());

#endif  // #ifndef SENSOR_GPS_HPP
