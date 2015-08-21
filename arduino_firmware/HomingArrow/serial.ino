#include "serial.h"

void serial_setup()
{

    _serial.data_received.reserve(100);
    Serial.begin(_serial.baud_rate);
    Serial.print(homing_arrow.name);
    Serial.print(" ");
    Serial.print(homing_arrow.version);
    Serial.print("\n");
}

void serial_loop()
{

    char * input;

    while (Serial.available()) {
        char incomingByte = (char) Serial.read();

        if (incomingByte == '\n') {
            _serial.reading_complete = true;
        } else {
            _serial.data_received += incomingByte;
        }
    }

    if (_serial.reading_complete) {
        if (_serial.data_received == F("ping")) {
            Serial.print("ok 1\n");
            Serial.print("pong\n");
        } else if (_serial.data_received == F("status")) {
            Serial.print(F("ok 0\n"));
            Serial.print(F("current_lat: "));
            Serial.print(rad2deg(gps.current_lat), 8);
            Serial.print(F("\n"));
            Serial.print(F("current_lon: "));
            Serial.print(rad2deg(gps.current_lon), 8);
            Serial.print(F("\n"));
            Serial.print(F("target_lat: "));
            Serial.print(rad2deg(gps.target_lat), 8);
            Serial.print(F("\n"));
            Serial.print(F("target_lon: "));
            Serial.print(rad2deg(gps.target_lon), 8);
            Serial.print(F("\n"));
            Serial.print(F("gps_az: "));
            Serial.print(rad2deg(gps.azimuth), 1);
            Serial.print(F("\n"));
            Serial.print(F("distance: "));
            Serial.print(gps.distance, 1);
            Serial.print(F("\n"));
            Serial.print(F("on_target: "));
            Serial.print(gps.on_target ? F("True") : F("False"));
            Serial.print(F("\n"));
            Serial.print(F("encoder_az: "));
            Serial.print(rad2deg(encoder.azimuth), 1);
            Serial.print(F("\n"));
            Serial.print(F("compass_az: "));
            Serial.print(rad2deg(compass.azimuth), 1);
            Serial.print(F("\n"));
            Serial.print(F("magnetic_declination: "));
            Serial.print(rad2deg(COMPASS_MAGNETIC_DECLINATION), 2);
            Serial.print(F("\n"));
            Serial.print(F("arrow_az: "));
            Serial.print(rad2deg(status.azimuth), 1);
            Serial.print(F("\n"));
            Serial.print(F("delta_az: "));
            Serial.print(rad2deg(status.azimuth_delta), 1);
            Serial.print(F("\n"));
            
        } else if (_serial.data_received.substring(0, 11) == F("set_target ")) {
            gps.target_lat = deg2rad(partialString(_serial.data_received.substring(11), ',', 0).toFloat());
            gps.target_lon = deg2rad(partialString(_serial.data_received.substring(11), ',', 1).toFloat());
            Serial.print(F("ok 2\n"));
            Serial.print(rad2deg(gps.target_lat), 8);
            Serial.print(F("\n"));
            Serial.print(rad2deg(gps.target_lon), 8);
            Serial.print(F("\n"));
            _loop.slow_timer = 0;
        } else if (_serial.data_received.substring(0, 9) == F("set_zone ")) {
            gps.target_zone = _serial.data_received.substring(9).toFloat();
            Serial.print(F("ok 1\n"));
            Serial.print(rad2deg(gps.target_zone), 1);
            Serial.print(F("\n"));
        } else if (_serial.data_received == F("set_north")) {
            encoder.set_north = true;  // read in encoder_loop()
            compass.set_north = true;  // read in compass_loop()
            Serial.print(F("ok 0\n"));
        } else {
        	Serial.print(F("error 2\n"));
        	Serial.print(F("Unknown command\n"));
            Serial.print(_serial.data_received);
            Serial.print("\n");
        }

        _serial.reading_complete = false;
        _serial.data_received = "";
    }
}
