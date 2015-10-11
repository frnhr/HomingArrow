#include "serial.h"

void serial_setup()
{
    _serial.data_received.reserve(100);

    Serial.begin(SERIAL_BAUD_RATE);
    Serial.print(F(NAME));
    Serial.print(F(" "));
    Serial.print(F(VERSION));
    Serial.print(F("\n"));
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
            Serial.print(F("ok 2\n"));
            Serial.print(F(NAME));
            Serial.print(F("\n"));
            Serial.print(F(VERSION));
            Serial.print(F("\n"));
        } else if (_serial.data_received == F("stop")) {
            Serial.print(F("ok 1\n"));
            compass.run = false;
        } else if (_serial.data_received == F("start")) {
            Serial.print(F("ok 1\n"));
            compass.run = true;
        } else if (_serial.data_received == F("x_min")) {
            Serial.print(F("ok 1\n"));
            _compass.x_min =  1 * COMPASS_UNCALIBRATED_MAX;
        } else if (_serial.data_received == F("x_max")) {
            Serial.print(F("ok 1\n"));
            _compass.x_max =  -1 * COMPASS_UNCALIBRATED_MAX;
        } else if (_serial.data_received == F("y_min")) {
            Serial.print(F("ok 1\n"));
            _compass.y_min =  1 * COMPASS_UNCALIBRATED_MAX;
        } else if (_serial.data_received == F("y_max")) {
            Serial.print(F("ok 1\n"));
            _compass.y_max =  -1 * COMPASS_UNCALIBRATED_MAX;
        } else if (_serial.data_received == F("z_min")) {
            Serial.print(F("ok 1\n"));
            _compass.z_min =  1 * COMPASS_UNCALIBRATED_MAX;
        } else if (_serial.data_received == F("z_max")) {
            Serial.print(F("ok 1\n"));
            _compass.z_max =  -1 * COMPASS_UNCALIBRATED_MAX;
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
