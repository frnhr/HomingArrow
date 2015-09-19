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
            Serial.print(F("ok 2\n"));
            Serial.print(homing_arrow.name);
            Serial.print(F("\n"));
            Serial.print(homing_arrow.version);
            Serial.print(F("\n"));
        } else if (_serial.data_received == F("status")) {
            Serial.print(F("ok 13\n"));
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
            Serial.print(F("distance: "));
            Serial.print(gps.distance, 1);
            Serial.print(F("\n"));
            Serial.print(F("gps_fix: "));
            Serial.print(gps.fix ? F("True") : F("False"));
            Serial.print(F("\n"));
            Serial.print(F("delta_az: "));
            Serial.print(rad2deg(status.azimuth_delta), 1);
            Serial.print(F("\n"));
            Serial.print(F("hardware_offset: "));
            Serial.print(rad2deg(encoder.offset), 1);
            Serial.print(F("\n"));
            Serial.print(F("on_target: "));
            Serial.print(gps.on_target ? F("True") : F("False"));
            Serial.print(F("\n"));
            Serial.print(F("target_zone: "));
            Serial.print(gps.target_zone, 1);
            Serial.print(F("\n"));
            Serial.print(F("magnetic_declination: "));
            Serial.print(rad2deg(COMPASS_MAGNETIC_DECLINATION), 2);
            Serial.print(F("\n"));
            Serial.print(F("battery_v: "));
            Serial.print(battery.voltage, 2);
            Serial.print(F("\n"));
            Serial.print(F("battery_low: "));
            Serial.print(battery.is_low ? F("True") : F("False"));
            Serial.print(F("\n"));
            
        } else if (_serial.data_received.substring(0, 11) == F("set_target ")) {
            if (_serial.data_received.substring(11) == F("N")) {
                gps.set_target_lat = deg2rad(90.0);
                gps.set_target_lon = 0.0;
            }
            else if (_serial.data_received.substring(11) == F("S")) {
                gps.set_target_lat = deg2rad(-90.0);
                gps.set_target_lon = 0.0;
            } else {
                gps.set_target_lat = deg2rad(partialString(_serial.data_received.substring(11), ',', 0).toFloat());
                gps.set_target_lon = deg2rad(partialString(_serial.data_received.substring(11), ',', 1).toFloat());
            }
            Serial.print(F("ok 2\n"));
            Serial.print(rad2deg(gps.set_target_lat), 8);
            Serial.print(F("\n"));
            Serial.print(rad2deg(gps.set_target_lon), 8);
            Serial.print(F("\n"));
            _loop.slow_timer = 0;
        } else if (_serial.data_received.substring(0, 9) == F("set_zone ")) {
            gps.target_zone = _serial.data_received.substring(9).toFloat();
            Serial.print(F("ok 1\n"));
            Serial.print(gps.target_zone, 1);
            Serial.print(F("\n"));
        } else if (_serial.data_received.substring(0, 11) == F("set_offset ")) {
            encoder.offset = deg2rad(_serial.data_received.substring(11).toFloat());
            Serial.print(F("ok 1\n"));
            Serial.print(rad2deg(encoder.offset), 1);
            Serial.print(F("\n"));
        } else if (_serial.data_received == F("compass_data")) {
            Serial.print(F("ok 5\n"));
            Serial.print("Inited:\t");
            Serial.print(compass.inited ? F("Yes") : F("No"));
            Serial.print("\n");
            Serial.print("magData:\t");
            Serial.print(_compass.sensor.magData.x);
            Serial.print(" ");
            Serial.print(_compass.sensor.magData.y);
            Serial.print(" ");
            Serial.print(_compass.sensor.magData.z);
            Serial.print("\n");
            Serial.print("accelData:\t");
            Serial.print(_compass.sensor.accelData.x);
            Serial.print(" ");
            Serial.print(_compass.sensor.accelData.y);
            Serial.print(" ");
            Serial.print(_compass.sensor.accelData.z);
            Serial.print("\n");
            Serial.print("alpha x y:\t");
            Serial.print(_compass.alpha_x);
            Serial.print(" ");
            Serial.print(_compass.alpha_y);
            Serial.print("\n");
            Serial.print("corrected:\t");
            Serial.print(_compass.corrected_x);
            Serial.print(" ");
            Serial.print(_compass.corrected_y);
            Serial.print("\n");
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
