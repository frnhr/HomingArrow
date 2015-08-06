#include "serial.h"


void serial_setup()
{

    Serial.begin(_serial.baud_rate);
    Serial.print(c1.name);
    Serial.print(" ");
    Serial.print(c1.version);
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

        // status buffer:
        if (_serial.data_received == "status") {
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
            Serial.print(rad2deg(gps.azimuth), 8);
            Serial.print(F("\n"));
            Serial.print(F("distance: "));
            Serial.print(gps.distance, 1);
            Serial.print(F("\n"));
            Serial.print(F("on_target: "));
            Serial.print(gps.on_target ? F("True") : F("False"));
            Serial.print(F("\n"));
            Serial.print(F("encoder_az: "));
            Serial.print(encoder.azimuth);
            Serial.print(F("\n"));
            Serial.print(F("compass_az: "));
            Serial.print(compass.azimuth);
            Serial.print(F("\n"));
        } else if (_serial.data_received.substring(0, 11) == "set_target ") {
            gps.target_lat = deg2rad(partialString(_serial.data_received.substring(11), ',', 0).toFloat());
            gps.target_lon = deg2rad(partialString(_serial.data_received.substring(11), ',', 1).toFloat());
            Serial.print(F("ok 2\n"));
            Serial.print(rad2deg(gps.target_lat), 8);
            Serial.print(F("\n"));
            Serial.print(rad2deg(gps.target_lon), 8);
            Serial.print(F("\n"));
        } else if (_serial.data_received.substring(0, 12) == "set_current ") {
            // TODO mock only!
            gps.current_lat = deg2rad(partialString(_serial.data_received.substring(12), ',', 0).toFloat());
            gps.current_lon = deg2rad(partialString(_serial.data_received.substring(12), ',', 1).toFloat());
            Serial.print(F("ok 2\n"));
            Serial.print(rad2deg(gps.current_lat), 8);
            Serial.print(F("\n"));
            Serial.print(rad2deg(gps.current_lon), 8);
            Serial.print(F("\n"));
        } else if (_serial.data_received.substring(0, 9) == "set_zone ") {
            gps.target_zone = _serial.data_received.substring(9).toFloat();
            Serial.print(F("ok 1\n"));
            Serial.print(rad2deg(gps.target_zone), 1);
            Serial.print(F("\n"));
        } else if (_serial.data_received == "set_north") {
            encoder.offset = encoder.azimuth;
            compass.offset = compass.azimuth;
            Serial.print(F("ok 0\n"));
        } else {
        	Serial.print(F("error 1\n"));
        	Serial.print(F("Unknown command\n"));
        }

        _serial.reading_complete = false;
        _serial.data_received = "";
    }
}
