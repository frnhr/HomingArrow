#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303.h>
#include "compass.h"


void compass_setup(void) 
{
    /* Initialise the sensor */
    if(!_compass.sensor.begin()) {
        /* There was a problem detecting the HMC5883 ... check your connections */
        Serial.print(F("Ooops, no LS303 detected ... Check your wiring!\n"));
        delay(500);
        while(1);
    }
}


void compass_loop(void) 
{
    if (! compass.run) {
        return;
    }

    _compass.sensor.read();
    if (_compass.sensor.magData.x < _compass.x_min) {
        _compass.x_min = _compass.sensor.magData.x;
        _compass.just_updated = true;
    }
    if (_compass.sensor.magData.x > _compass.x_max) {
        _compass.x_max = _compass.sensor.magData.x;
        _compass.just_updated = true;
    }
    if (_compass.sensor.magData.y < _compass.y_min) {
        _compass.y_min = _compass.sensor.magData.y;
        _compass.just_updated = true;
    }
    if (_compass.sensor.magData.y > _compass.y_max) {
        _compass.y_max = _compass.sensor.magData.y;
        _compass.just_updated = true;
    }
    if (_compass.sensor.magData.z < _compass.z_min) {
        _compass.z_min = _compass.sensor.magData.z;
        _compass.just_updated = true;
    }
    if (_compass.sensor.magData.z > _compass.z_max) {
        _compass.z_max = _compass.sensor.magData.z;
        _compass.just_updated = true;
    }

    _compass.x_p = (_compass.sensor.magData.x - ((_compass.x_max + _compass.x_min) / 2)) / ((_compass.x_max - _compass.x_min) / 2);
    _compass.y_p = (_compass.sensor.magData.y - ((_compass.y_max + _compass.y_min) / 2)) / ((_compass.y_max - _compass.y_min) / 2);
    _compass.z_p = (_compass.sensor.magData.z - ((_compass.z_max + _compass.z_min) / 2)) / ((_compass.z_max - _compass.z_min) / 2);

    _compass.active_axes = 'x';
    if (abs(_compass.y_p) > abs(_compass.x_p)) {
        _compass.active_axes = 'y';        
    }
    if (abs(_compass.z_p) > abs(_compass.x_p) &&
            abs(_compass.z_p) > abs(_compass.y_p) ) {
        _compass.active_axes = 'z';        
    }

    if (_compass.just_updated) {
        compass.just_updated = true;
        _compass.pass++;
    }

}

void compass_serial_loop() 
{
    if (! compass.run) {
        return;
    }
    
    compass.just_updated = false;

    Serial.print(F("\n"));
    Serial.print(F("CALIBRATION UPDATE "));
    Serial.print(_compass.pass);
    if (_compass.just_updated) {
        Serial.print(F(" +++++++++++++++++++++++++"));
    }
    Serial.print(F("\n"));
    Serial.print(F("    X: "));
    Serial.print(_compass.x_min);
    Serial.print(F(" - "));
    Serial.print(_compass.x_max);
    if (_compass.active_axes == 'x') {
        Serial.print(F("  *  "));
        Serial.print(_compass.x_p * 100, 1);
        Serial.print(F("% ("));
        Serial.print(_compass.sensor.magData.x);
        Serial.print(F(")"));
    }
    Serial.print(F("\n"));
    Serial.print(F("    Y: "));
    Serial.print(_compass.y_min);
    Serial.print(F(" - "));
    Serial.print(_compass.y_max);
    if (_compass.active_axes == 'y') {
        Serial.print(F("  *  "));
        Serial.print(_compass.y_p * 100, 1);
        Serial.print(F("% ("));
        Serial.print(_compass.sensor.magData.y);
        Serial.print(F(")"));
    }
    Serial.print(F("\n"));
    Serial.print(F("    Z: "));
    Serial.print(_compass.z_min);
    Serial.print(F(" - "));
    Serial.print(_compass.z_max);
    if (_compass.active_axes == 'z') {
        Serial.print(F("  *  "));
        Serial.print(_compass.z_p * 100, 1);
        Serial.print(F("% ("));
        Serial.print(_compass.sensor.magData.z);
        Serial.print(F(")"));
    }
    Serial.print(F("\n"));
    Serial.print(F("\n"));
    Serial.print(F("calibrate "));
    Serial.print(_compass.x_min);
    Serial.print(F(","));
    Serial.print(_compass.x_max);
    Serial.print(F(","));
    Serial.print(_compass.y_min);
    Serial.print(F(","));
    Serial.print(_compass.y_max);
    Serial.print(F(","));
    Serial.print(_compass.z_min);
    Serial.print(F(","));
    Serial.print(_compass.z_max);
    Serial.print(F("\n"));
    Serial.print(F("\n"));
    Serial.print(F("\n"));

    if (_compass.just_updated) {
        compass.just_updated = true;
        _compass.just_updated = false;
    }

    
}