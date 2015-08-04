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
            Serial.print(rad2deg(gps.current_lat));
            Serial.print(F("\n"));
            Serial.print(F("current_lon: "));
            Serial.print(rad2deg(gps.current_lon));
            Serial.print(F("\n"));
            Serial.print(F("target_lat: "));
            Serial.print(rad2deg(gps.target_lat));
            Serial.print(F("\n"));
            Serial.print(F("target_lon: "));
            Serial.print(rad2deg(gps.target_lon));
            Serial.print(F("\n"));
            Serial.print(F("gps_az: "));
            Serial.print(rad2deg(gps.azimuth));
            Serial.print(F("\n"));
            Serial.print(F("distance: "));
            Serial.print(gps.distance);
            Serial.print(F("\n"));
        } else {
        	Serial.print(F("error 1\n"));
        	Serial.print(F("Unknown command\n"));
        }

        _serial.reading_complete = false;
        _serial.data_received = "";
    }
}
