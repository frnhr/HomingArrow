#include <Arduino.h>
#include "modules.hpp"


#ifdef PROTOCOL_INO_HPP
#error The .ino.hpp file of a module can be included only once (and should be included from main.ino). Did you wanted to include the .h file instead?
#endif
#define PROTOCOL_INO_HPP
#include "_protocol.hpp"


#ifndef DEVICE_NAME
  #define DEVICE_NAME "Unnamed device"
#endif

#ifndef DEVICE_VERSION
  #define DEVICE_VERSION "0.0.0"
#endif


void Protocol::setup()
{}


void Protocol::loop()
{
  // we are only conserned with handling incomming commands:
  if (setCommand[0] == '\0') {
    // (empty strings start with a null-character)
    return;
  }

  if (!setReplyPrinter) {
    // reply printer must also be set
    // TODO use Serial only in DEBUG mode!
    Serial.print(F("Got a command but no printer!\n"));
    setCommand[0] = '\0';
    return;
  }

  // store replyPrinter locally to avoid accidental overwrite by other modules:
  replyPrinter = setReplyPrinter;
  // clear the public setter:
  setReplyPrinter = nullptr;


  // we'll need a fancy String object, for simpler parsing:
  String command = setCommand;

  // set busy flag (just in case we have to handle this command over multiple cycles):
  busy = true;

  // handle actual commands:

  if (command == F("ping")) {
      replyPrinter->print(F("ok 2\n"));
      replyPrinter->print(DEVICE_NAME);
      replyPrinter->print(F("\n"));
      replyPrinter->print(DEVICE_VERSION);
      replyPrinter->print(F("\n"));

  } else if (command == "status") {

    // calculate how many lines are going to be in the reply:
    int statusReplyCount = 3;  // 3 lines form protocol module
    #ifdef BLINK_HPP
      statusReplyCount += 1;
    #endif
    #ifdef SENSOR_ENCODER_HPP
      statusReplyCount += 3;
    #endif
    #ifdef SENSOR_GPS_HPP
      statusReplyCount += 3;
    #endif
    #ifdef SENSOR_MAG_ACC_HPP
      statusReplyCount += 3;
    #endif
    #ifdef ACCELEROMETER_HPP
      statusReplyCount += 5;
    #endif
    #ifdef MAGNETOMETER_HPP
      statusReplyCount += 5;
    #endif
    #ifdef ACC_CALIBRATION_HPP
      statusReplyCount += 7;
    #endif
    #ifdef MAG_CALIBRATION_HPP
      statusReplyCount += 7;
    #endif
    #ifdef DECLINATION_HPP
      statusReplyCount += 3;
    #endif
    #ifdef ARROW_HPP
      statusReplyCount += 3;
    #endif
    #ifdef COMPASS_HPP
      statusReplyCount += 5;
    #endif
    #ifdef SERIAL_COMM_HPP
      statusReplyCount += 1;
    #endif

    // first line of the reply, with the number of lines to follow:
    replyPrinter->print(F("status "));
    replyPrinter->print(statusReplyCount);
    replyPrinter->print(F("\n"));

    // reply from protocol module:
    replyPrinter->print(F("[protocol]\n"));
    replyPrinter->print(F("name: "));
    replyPrinter->print(DEVICE_NAME);
    replyPrinter->print(F("\n"));
    replyPrinter->print(F("version: "));
    replyPrinter->print(DEVICE_VERSION);
    replyPrinter->print(F("\n"));

    // replies with statuses from other modules:

    #ifdef SENSOR_ENCODER_HPP
      replyPrinter->print(F("[sensor_encoder]\n"));
      replyPrinter->print(F("init: "));
      replyPrinter->print(sensor_encoder->inited);
      replyPrinter->print(F("\n"));
      replyPrinter->print(F("azimuth: "));
      replyPrinter->print(rad2deg(sensor_encoder->azimuth));
      replyPrinter->print(F("\n"));
    #endif

    #ifdef SENSOR_MAG_ACC
      replyPrinter->print(F("[sensor_mag_acc]\n"));
      replyPrinter->print(F("init: "));
      replyPrinter->print(sensor_mag_acc->inited);
      replyPrinter->print(F("\n"));
      replyPrinter->print(F("azimuth: "));
      replyPrinter->print(rad2deg(sensor_mag_acc->azimuth));
      replyPrinter->print(F("\n"));
    #endif

    #ifdef SENSOR_GPS_HPP
      replyPrinter->print(F("[sensor_gps]\n"));
      replyPrinter->print(F("init: "));
      replyPrinter->print(sensor_gps->inited);
      replyPrinter->print(F("\n"));
      replyPrinter->print(F("fix: "));
      replyPrinter->print(sensor_gps->fix);
      replyPrinter->print(F("\n"));
    #endif

    #ifdef SENSOR_MAG_ACC_HPP
      replyPrinter->print(F("[sensor_mag_acc]\n"));
      replyPrinter->print(F("init: "));
      replyPrinter->print(sensor_mag_acc->inited);
      replyPrinter->print(F("\n"));
      replyPrinter->print(F("connected: "));
      replyPrinter->print(sensor_mag_acc->connected);
      replyPrinter->print(F("\n"));
    #endif

    #ifdef ACCELEROMETER_HPP
      replyPrinter->print(F("[accelerometer]\n"));
      replyPrinter->print(F("init: "));
      replyPrinter->print(accelerometer->inited);
      replyPrinter->print(F("\n"));
      replyPrinter->print(F("x: "));
      replyPrinter->print(rad2deg(accelerometer->x));
      replyPrinter->print(F("\n"));
      replyPrinter->print(F("y: "));
      replyPrinter->print(rad2deg(accelerometer->y));
      replyPrinter->print(F("\n"));
      replyPrinter->print(F("z: "));
      replyPrinter->print(rad2deg(accelerometer->z));
      replyPrinter->print(F("\n"));
    #endif

    #ifdef MAGNETOMETER_HPP
      replyPrinter->print(F("[magnetometer]\n"));
      replyPrinter->print(F("init: "));
      replyPrinter->print(magnetometer->inited);
      replyPrinter->print(F("\n"));
      replyPrinter->print(F("x: "));
      replyPrinter->print(rad2deg(magnetometer->x));
      replyPrinter->print(F("\n"));
      replyPrinter->print(F("y: "));
      replyPrinter->print(rad2deg(magnetometer->y));
      replyPrinter->print(F("\n"));
      replyPrinter->print(F("z: "));
      replyPrinter->print(rad2deg(magnetometer->z));
      replyPrinter->print(F("\n"));
    #endif

    #ifdef ACC_CALIBRATION_HPP
      replyPrinter->print(F("[acc_calibration]\n"));
      replyPrinter->print(F("init: "));
      replyPrinter->print(acc_calibration->inited);
      replyPrinter->print(F("\n"));
      replyPrinter->print(F("calibrated: "));
      replyPrinter->print(acc_calibration->calibrated);
      replyPrinter->print(F("\n"));
      replyPrinter->print(F("calibrating: "));
      replyPrinter->print(acc_calibration->calibrating);
      replyPrinter->print(F("\n"));
      replyPrinter->print(F("range_x: "));
      replyPrinter->print(acc_calibration->x_min);
      replyPrinter->print(F(", "));
      replyPrinter->print(acc_calibration->x_max);
      replyPrinter->print(F("\n"));
      replyPrinter->print(F("range_y: "));
      replyPrinter->print(acc_calibration->y_min);
      replyPrinter->print(F(", "));
      replyPrinter->print(acc_calibration->y_max);
      replyPrinter->print(F("\n"));
      replyPrinter->print(F("range_z: "));
      replyPrinter->print(acc_calibration->z_min);
      replyPrinter->print(F(", "));
      replyPrinter->print(acc_calibration->z_max);
      replyPrinter->print(F("\n"));
    #endif

    #ifdef MAG_CALIBRATION_HPP
      replyPrinter->print(F("[mag_calibration]\n"));
      replyPrinter->print(F("init: "));
      replyPrinter->print(mag_calibration->inited);
      replyPrinter->print(F("\n"));
      replyPrinter->print(F("calibrated: "));
      replyPrinter->print(mag_calibration->calibrated);
      replyPrinter->print(F("\n"));
      replyPrinter->print(F("calibrating: "));
      replyPrinter->print(mag_calibration->calibrating);
      replyPrinter->print(F("\n"));
      replyPrinter->print(F("range_x: "));
      replyPrinter->print(mag_calibration->x_min);
      replyPrinter->print(F(", "));
      replyPrinter->print(mag_calibration->x_max);
      replyPrinter->print(F("\n"));
      replyPrinter->print(F("range_y: "));
      replyPrinter->print(mag_calibration->y_min);
      replyPrinter->print(F(", "));
      replyPrinter->print(mag_calibration->y_max);
      replyPrinter->print(F("\n"));
      replyPrinter->print(F("range_z: "));
      replyPrinter->print(mag_calibration->z_min);
      replyPrinter->print(F(", "));
      replyPrinter->print(mag_calibration->z_max);
      replyPrinter->print(F("\n"));
    #endif

    #ifdef DECLINATION_HPP
      replyPrinter->print(F("[declination]\n"));
      replyPrinter->print(F("init: "));
      replyPrinter->print(declination->inited);
      replyPrinter->print(F("\n"));
      replyPrinter->print(F("declination: "));
      replyPrinter->print(rad2deg(declination->declination));
      replyPrinter->print(F("\n"));
    #endif

    #ifdef ARROW_HPP
      replyPrinter->print(F("[arrow]\n"));
      replyPrinter->print(F("init: "));
      replyPrinter->print(arrow->inited);
      replyPrinter->print(F("\n"));
      replyPrinter->print(F("azimuth: "));
      replyPrinter->print(rad2deg(arrow->azimuth));
      replyPrinter->print(F("\n"));
    #endif


    #ifdef SERIAL_COMM_HPP
      replyPrinter->print(F("[serial_comm]\n"));
    #endif


    #ifdef BLINK_HPP
      replyPrinter->print(F("blink_pattern: "));
      replyPrinter->print(blink->pattern_i);
      replyPrinter->print(F("\n"));
    #endif  //#ifdef BLINK_HPP

/*
      replyPrinter->print(rad2deg(gps->current_lat), 8);

      replyPrinter->print(F("current_lat: "));
      replyPrinter->print(rad2deg(gps->current_lat), 8);
      replyPrinter->print(F("\n"));
      replyPrinter->print(F("current_lon: "));
      replyPrinter->print(rad2deg(gps->current_lon), 8);
      replyPrinter->print(F("\n"));
      replyPrinter->print(F("target_lat: "));
      replyPrinter->print(rad2deg(gps->target_lat), 8);
      replyPrinter->print(F("\n"));
      replyPrinter->print(F("target_lon: "));
      replyPrinter->print(rad2deg(gps->target_lon), 8);
      replyPrinter->print(F("\n"));
      replyPrinter->print(F("distance: "));
      replyPrinter->print(gps->distance, 1);
      replyPrinter->print(F("\n"));
      replyPrinter->print(F("on_target: "));
      replyPrinter->print(gps->on_target ? F("True") : F("False"));
      replyPrinter->print(F("\n"));
      replyPrinter->print(F("target_zone: "));
      replyPrinter->print(gps->target_zone, 1);
      replyPrinter->print(F("\n"));
      replyPrinter->print(F("gps_fix: "));
      replyPrinter->print(gps->fix ? F("True") : F("False"));
      replyPrinter->print(F("\n"));
      replyPrinter->print(F("gps_showing_home: "));
      replyPrinter->print(gps->fix ? F("True") : F("False"));
      replyPrinter->print(F("\n"));
    #endif  //#ifdef GPS_HPP

    */
/*
    replyPrinter->print(F("azimuth: "));
    replyPrinter->print(rad2deg(status->azimuth));
    replyPrinter->print(F(" "));
    replyPrinter->print(rad2deg(compass->azimuth));
    replyPrinter->print(F(" "));
    replyPrinter->print(rad2deg(encoder->azimuth));
    replyPrinter->print(F("\n"));
    replyPrinter->print(F("delta_az: "));
    replyPrinter->print(rad2deg(status->azimuth_delta), 1);
    replyPrinter->print(F("\n"));
    replyPrinter->print(F("hardware_offset: "));
    replyPrinter->print(rad2deg(encoder->offset), 1);
    replyPrinter->print(F("\n"));
    replyPrinter->print(F("magnetic_declination: "));
    replyPrinter->print(rad2deg(COMPASS_MAGNETIC_DECLINATION), 2);
    replyPrinter->print(F("\n"));
    replyPrinter->print(F("battery_v: "));
    replyPrinter->print(battery->voltage, 2);
    replyPrinter->print(F("\n"));
    replyPrinter->print(F("battery_low: "));
    replyPrinter->print(battery->is_low ? F("True") : F("False"));
    replyPrinter->print(F("\n"));
*/


/*
    } else if (_serial.data_received.substring(0, 11) == F("set_target ")) {
        if (_serial.data_received.substring(11) == F("N")) {
            gps->set_target_lat = deg2rad(90.0);
            gps->set_target_lon = 0.0;
        }
        else if (_serial.data_received.substring(11) == F("S")) {
            gps->set_target_lat = deg2rad(-90.0);
            gps->set_target_lon = 0.0;
        } else {
            gps->set_target_lat = deg2rad(partialString(_serial.data_received.substring(11), ',', 0).toFloat());
            gps->set_target_lon = deg2rad(partialString(_serial.data_received.substring(11), ',', 1).toFloat());
        }
        replyPrinter->print(F("ok 2\n"));
        replyPrinter->print(rad2deg(gps->set_target_lat), 8);
        replyPrinter->print(F("\n"));
        replyPrinter->print(rad2deg(gps->set_target_lon), 8);
        replyPrinter->print(F("\n"));
        _loop.slow_timer = 0;
    } else if (_serial.data_received.substring(0, 9) == F("set_zone ")) {
        gps->target_zone = _serial.data_received.substring(9).toFloat();
        replyPrinter->print(F("ok 1\n"));
        replyPrinter->print(gps->target_zone, 1);
        replyPrinter->print(F("\n"));
    } else if (_serial.data_received.substring(0, 11) == F("set_offset ")) {
        encoder.offset = deg2rad(_serial.data_received.substring(11).toFloat());
        replyPrinter->print(F("ok 1\n"));
        replyPrinter->print(rad2deg(encoder.offset), 1);
        replyPrinter->print(F("\n"));
    } else if (_serial.data_received == F("compass_data")) {
        replyPrinter->print(F("ok 4\n"));
        replyPrinter->print("Inited:\t");
        replyPrinter->print(compass.inited ? F("Yes") : F("No"));
        replyPrinter->print("\n");
        replyPrinter->print("magData:\t");
        replyPrinter->print(_compass.sensor.magData.x);
        replyPrinter->print(" ");
        replyPrinter->print(_compass.sensor.magData.y);
        replyPrinter->print(" ");
        replyPrinter->print(_compass.sensor.magData.z);
        replyPrinter->print("\n");
        replyPrinter->print("accelData:\t");
        replyPrinter->print(_compass.sensor.accelData.x);
        replyPrinter->print(" ");
        replyPrinter->print(_compass.sensor.accelData.y);
        replyPrinter->print(" ");
        replyPrinter->print(_compass.sensor.accelData.z);
        replyPrinter->print("\n");
        replyPrinter->print("roll pitch yaw:\t");
        replyPrinter->print(rad2deg(_compass.phi));
        replyPrinter->print(" ");
        replyPrinter->print(rad2deg(_compass.theta));
        replyPrinter->print(" ");
        replyPrinter->print(rad2deg(_compass.psi));
        replyPrinter->print("\n");
        replyPrinter->print("alpha delta:\t");
        replyPrinter->print(rad2deg(_compass.alpha));
        replyPrinter->print(" ");
        replyPrinter->print(rad2deg(_compass.delta));
        replyPrinter->print("\n");
    } else if (_serial.data_received == F("gps_override off")) {
        replyPrinter->print(F("ok 1\n"));
        _gps->override = false;
        _loop.slow_timer = 0;
    } else if (_serial.data_received.substring(0, 13) == F("gps_override ")) {
        gps->current_lat = deg2rad(partialString(_serial.data_received.substring(13), ',', 0).toFloat());
        gps->current_lon = deg2rad(partialString(_serial.data_received.substring(13), ',', 1).toFloat());
        _gps->override = true;
        replyPrinter->print(F("ok 2\n"));
        replyPrinter->print(rad2deg(gps->current_lat), 8);
        replyPrinter->print(F("\n"));
        replyPrinter->print(rad2deg(gps->current_lon), 8);
        replyPrinter->print(F("\n"));
        _loop.slow_timer = 0;

*/

#ifdef DECLINATION_HPP

} else if (command == "declination") {
  replyPrinter->print(F("declination 1\n"));
  if (isCloseTo(declination->declination, DECLINATION_NULL_VALUE, DECLINATION_NULL_EPSILON)) {
    replyPrinter->print(F("not_set"));
  } else {
    replyPrinter->print(declination->declination);
  }
  replyPrinter->print(F("\n"));

} else if (command.substring(0, 16) == "declination set ") {
  String data = command.substring(16);
  char buf[data.length() + 1];
  data.toCharArray(buf, data.length() + 1);
  float value = atof(buf);
  declination->setDeclination = value;
  replyPrinter->print(F("ok 1\n"));
  replyPrinter->print(value);
  replyPrinter->print(F("\n"));

  #endif  // #ifdef DECLINATION_HPP


  // unknown command:

  } else {
    replyPrinter->print(F("error 2\n"));
    replyPrinter->print(F("unknown command\n"));
    replyPrinter->print(command);
    replyPrinter->print(F("\n"));
  }

  // add an extra new line, just in case:
  replyPrinter->print(F("\n"));

  // reset flags:
  setCommand[0] = '\0';
  busy = false;

  // also clear reference to the printer, for good measure:
  replyPrinter = nullptr;
}
